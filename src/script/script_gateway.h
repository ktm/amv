//
// Created by ktm on 2/4/16.
//

#ifndef AMVMODEL_SCRIPT_GATEWAY_H
#define AMVMODEL_SCRIPT_GATEWAY_H

#include <string>

class script_gateway {
public:
    virtual bool evaluate_condition(std::string condition) = 0;
    virtual void call(std::string fxnname, std::string argnames[]) = 0;
    virtual void write_to_js(std::string name, std::string value) = 0;
};
#endif //AMVMODEL_SCRIPT_GATEWAY_H
