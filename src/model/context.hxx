//
// Created by ktm on 9/9/15.
//

#ifndef AMVMODEL_CONTEXT_H
#define AMVMODEL_CONTEXT_H

#include <mutex>
#include "process_node.hxx"
#include "../collection/name_value_pair.hxx"
#include "../collection/threadsafe_queue.hxx"
#include "event_callback_container.hxx"

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

    Context():contextData(24) {};
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

    NameValuePairPtr _write(string name, string value) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        NameValuePairPtr npp = find(name);
        if (npp == nullptr) {
            npp = make_shared<NameValuePair>(name, value);
            contextData.push_back(npp);
        } else {
            npp->second = value;
        }
        return npp;
    }

public:
    static Context& Instance() {
        static Context CTX;
        return CTX;
    }

    NameValuePairPtr write(NameValuePairPtr nvp) {
        return write(nvp->first, nvp->second);
    }

    NameValuePairPtr write(string name, string value) {
        NameValuePairPtr nvp = _write(name, value);
        EventCallbackContainer::Instance().fireEvent(nvp);
        return nvp;
    }

    string read(string name) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        NameValuePairPtr npp = find(name);
        if (npp != nullptr) {
            return npp->second;
        }
        return "";  // really want to return nullptr here but it breaks stuff
    }
};

#endif //AMVMODEL_CONTEXT_H
