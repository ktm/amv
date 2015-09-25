//
// Created by ktm on 9/9/15.
//

#ifndef AMVMODEL_CONTEXT_H
#define AMVMODEL_CONTEXT_H

#include <mutex>
#include "process_node.hxx"
#include "../collection/name_value_pair.hxx"
#include "../collection/threadsafe_queue.hxx"

/*
 *
 * The context is not expected to hold more than a few dozen elements, so we follow
 * the heuristic set forth here:
 * http://scottmeyers.blogspot.com/2015/09/should-you-be-using-something-instead.html
 *
 */
class Context {
    std::vector<NameValuePairPtr> contextData;
    std::mutex data_mutex;
    threadsafe_queue<string> change_queue;

    Context():contextData(24),change_queue() {};
    ~Context() {};

    NameValuePairPtr find(string name) {
        auto list = find_if(contextData.begin(), contextData.end(),
                            [name](NameValuePairPtr r) {
                                if (r == nullptr) {
                                    return false;  // this happens when contextData is empty and I think it's a bug
                                }
                                return ((r->first.compare(name) == 0));
                            });
        if (list == contextData.end()) {
            return nullptr;
        }
        return *list;
    }

    void _write(string name, string value) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        NameValuePairPtr npp = find(name);
        if (npp == nullptr) {
            contextData.push_back(make_shared<NameValuePair>(name, value));
        } else {
            npp->second = value;
        }
    }

public:
    static Context& Instance() {
        static Context CTX;
        return CTX;
    }

    void write(NameValuePairPtr nvp) {
        write(nvp->first, nvp->second);
    }

    void write(string name, string value) {
        _write(name, value);
        change_queue.push(name);
    }

    string read(string name) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        NameValuePairPtr npp = find(name);
        if (npp != nullptr) {
            return npp->second;
        }
        return "";
    }
};

#endif //AMVMODEL_CONTEXT_H
