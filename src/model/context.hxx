//
// Created by ktm on 9/9/15.
//

#ifndef AMVMODEL_CONTEXT_H
#define AMVMODEL_CONTEXT_H

#include <mutex>
#include "../collection/name_value_pair.hxx"
#include "../collection/threadsafe_queue.hxx"
#include "event_callback_container.hxx"
#include "../javascript/duktape.h"

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
    std::vector<NameValuePairPtr> contextData;
    std::mutex data_mutex;

    duk_context *js_context;

    Context():contextData(24) {
        js_context = duk_create_heap_default();
    };

    ~Context() {
        if (js_context != nullptr) {
            duk_destroy_heap(js_context);
        }
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
            contextData.push_back(npp);
            retval->first = true;
        } else {
            retval->first = (0 == value.compare(npp->second));
            npp->second = value;
        }
        retval->second = npp;
        write_to_js(name, value);
        return retval;
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

    duk_context* jsctx() {
        return js_context;
    }

    bool write_to_js(string name, string value) {
        duk_bool_t rc;

        duk_push_string(jsctx(), value.c_str());
        rc = duk_put_global_string(jsctx(), name.c_str());
        return rc;
    }

    bool evaluate_js_condition(std::string js) {
        duk_eval_string(jsctx(), js.c_str());
        bool retval = duk_get_boolean(jsctx(), -1);
        duk_pop(jsctx());
        return retval;
    }
};

#endif //AMVMODEL_CONTEXT_H
