//
// Created by ktm on 2/4/16.
//

#include <chaiscript/chaiscript.hpp>
#include <chaiscript/chaiscript_stdlib.hpp>
#include "chaiscript_gateway.h"
#include "../gps/gps.h"
#include "../serial/serial.h"
#include "../model/context.hxx"

chaiscript_gateway::chaiscript_gateway(): js_context(chaiscript::Std_Lib::library()) {
    js_context.add(chaiscript::fun(&serial_init),    "serialInit");
    js_context.add(chaiscript::fun(&serial_config),  "serialConfig");
    js_context.add(chaiscript::fun(&serial_println), "serialWrite");
    js_context.add(chaiscript::fun(&serial_readln),  "serialRead");
    js_context.add(chaiscript::fun(&serial_close),  "serialClose");
    js_context.add(chaiscript::fun(&update_gps_location),  "updateGPS");
}

bool chaiscript_gateway::evaluate_condition(std::string condition) {
    std::cout << "conditional: " << condition << std::endl;
    std::lock_guard<std::mutex> data_lock(data_mutex);
    bool retval = js_context.eval<bool>(condition);
    return retval;
}

double chaiscript_gateway::toNumber(std::string arg) {
    double retval = HUGE_VAL;

    char * endptr;
    double d = strtod(arg.c_str(), &endptr);
    if (arg.c_str() != endptr) {
        retval = d;
    }
    return retval;
}

void chaiscript_gateway::write_to_js(std::string name, Value value) {
    chaiscript::Boxed_Value v;

    if (value.which() == INT_VALUE) {
        v = chaiscript::Boxed_Value(boost::get<int>(value));
    } else if (value.which() == DOUBLE_VALUE) {
        v = chaiscript::Boxed_Value(boost::get<double >(value));
    } else if (value.which() == STRING_VALUE) {
        v = chaiscript::Boxed_Value(boost::get<std::string>(value));
    }
    js_context.set_global(v, name);
}

std::string chaiscript_gateway::createCallString(std::string fxnname, std::vector<std::string> args) {
    std::string callString(fxnname);
    callString.append("(");

    int n = args.size();
    for (int idx = 0; idx < n; ++idx) {
        Value value = (Context::Instance().read(args[idx]));
        if (value.which() == INT_VALUE) {
            callString.append(to_string(boost::get<int>(value)));
        } else if (value.which() == DOUBLE_VALUE) {
            callString.append(to_string(boost::get<double>(value)));
        } else if (value.which() == STRING_VALUE) {
            callString.append("\"");
            callString.append(boost::get<std::string>(value));
            callString.append("\"");
        }
        if (idx < n-1) {
            callString.append(",");
        }
    }
    callString.append(");");
    std::cout << callString << std::endl;
    return callString;
}