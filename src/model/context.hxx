//
// Created by ktm on 9/9/15.
//

#ifndef AMVMODEL_CONTEXT_H
#define AMVMODEL_CONTEXT_H

#include <mutex>
#include <stdlib.h>

#include "../collection/name_value_pair.hxx"
#include "../collection/threadsafe_queue.hxx"
#include "event_callback_container.hxx"

#include <chaiscript/chaiscript_stdlib.hpp>

using ContextChange = pair<bool, NameValuePairPtr>;
using ContextChangePtr = shared_ptr<ContextChange >;

/*
 *
 * The context is not expected to hold more than a few dozen elements, so we follow
 * the heuristic set forth here:
 * http://scottmeyers.blogspot.com/2015/09/should-you-be-using-something-instead.html
 *
 */
class Context {
#ifdef TEST
    friend class JSTest;
    friend class ProcessTest;
#endif

    std::vector<NameValuePairPtr> contextData;
    std::mutex data_mutex;
    chaiscript::ChaiScript js_context;

    Context():contextData(24),js_context(chaiscript::Std_Lib::library()) {
    };

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

    ContextChangePtr _write(string name, string value) {
        std::lock_guard<std::mutex> data_lock(data_mutex);

        NameValuePairPtr npp = find(name);
        ContextChangePtr retval = make_shared<ContextChange>(false, npp);

        if (npp == nullptr) {
            npp = make_shared<NameValuePair>(name, value);
            write_to_js(name, value);
            contextData.push_back(npp);
            retval->first = true;
        } else {
            retval->first = (0 != value.compare(npp->second));
            npp->second = value;
            if (retval->first) {
                write_to_js(name, value);
            }
        }
        retval->second = npp;

        return retval;
    }

    void write_to_js(string name, string value) {
        chaiscript::Boxed_Value v(value);
        double d = toNumber(value);
        if (HUGE_VAL != d) {
            v = chaiscript::Boxed_Value(d);
        }
        js_context.set_global(v, name);
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
        ContextChangePtr ccp = _write(name, value);
        if (ccp->first) {
            // the context was changed, so publish the new value
            EventCallbackContainer::Instance().fireEvent(name, ccp->second);
        }
        return ccp->second;
    }

    string read(string name) {
        std::lock_guard<std::mutex> data_lock(data_mutex);
        NameValuePairPtr npp = find(name);
        if (npp != nullptr) {
            return npp->second;
        }
        return "";  // really want to return nullptr here but it breaks stuff
    }

    double toNumber(std::string arg) {
        double retval = HUGE_VAL;

        char * endptr;
        double d = strtod(arg.c_str(), &endptr);
        if (arg.c_str() != endptr) {
            retval = d;
        }

        return retval;
    }

    bool evaluate_js_condition(std::string js) {
        cout << "evaluate_js_condition: " << js;
        std::lock_guard<std::mutex> data_lock(data_mutex);
        bool retval = js_context.eval<bool>(js);
        cout << ": " << retval << endl;

        return retval;
    }
};

#endif //AMVMODEL_CONTEXT_H
