//
// Created by ktm on 2/4/16.
//

#ifndef AMVMODEL_CHAI_SCRIPT_H
#define AMVMODEL_CHAI_SCRIPT_H

#include <chaiscript/chaiscript.hpp>
#include <mutex>
#include <boost/variant.hpp>
#include "../collection/name_value_pair.hxx"

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
    void write_to_js(std::string name, Value value);
    std::string createCallString(std::string fxnname, std::vector<std::string> args);

    //TIL template fxn defs go in the header, otherwise the linker fails
    template<typename ValueType> ValueType call(std::string fxnname, std::vector<std::string> args) {
        const std::string callString = createCallString(fxnname, args);
        chaiscript::Boxed_Value bv = chaiscript_gateway::Instance().js_context.eval(callString);

        auto info = bv.get_type_info();

        return chaiscript::boxed_cast<ValueType>(bv);
/*
        if (typeid(int) == *info.bare_type_info()) {
            return Value(chaiscript::boxed_cast<int>(bv));
        }
        if (typeid(double) == *info.bare_type_info()) {
            return Value(chaiscript::boxed_cast<double>(bv));
        }
        if (typeid(std::string) == *info.bare_type_info()) {
            std::string& string_ref = chaiscript::boxed_cast<std::string&>(bv);

            Value v(string_ref);

            return v;
        }
        return Value();
*/
    }
};


#endif //AMVMODEL_CHAI_SCRIPT_H
