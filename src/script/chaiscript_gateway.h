//
// Created by ktm on 2/4/16.
//

#ifndef AMVMODEL_CHAI_SCRIPT_H
#define AMVMODEL_CHAI_SCRIPT_H

#include <chaiscript/chaiscript.hpp>
#include <mutex>

class chaiscript_gateway {
    std::mutex data_mutex;
    double toNumber(std::string arg);
    chaiscript_gateway();

public:
    chaiscript::ChaiScript js_context;
    static chaiscript_gateway& Instance() {
        static chaiscript_gateway INSTANCE;
        return INSTANCE;
    }

    bool evaluate_condition(std::string condition);
    void write_to_js(std::string name, std::string value);
    std::string createCallString(std::string fxnname, std::string argname);

    //TIL template fxn defs go in the header, otherwise the linker fails
    template<typename Value> Value call(std::string fxnname, std::string argname) {
        const std::string callString = createCallString(fxnname, argname);
        chaiscript::Boxed_Value bv = chaiscript_gateway::Instance().js_context(callString);
        Value ret = chaiscript::boxed_cast<Value>(bv);
        return ret;
    }
};


#endif //AMVMODEL_CHAI_SCRIPT_H
