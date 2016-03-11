//
// Created by ktm on 8/14/15.
//

#define TEST

#include "ProcessTest.hxx"
#include "jstest.h"

int main() {

    chaiscript_gateway::Instance().registerFunction(&serial_config, "serialConfig");
    chaiscript_gateway::Instance().registerFunction(&serial_init, "serialInit");
    chaiscript_gateway::Instance().registerFunction(&serial_println, "serialWrite");
    chaiscript_gateway::Instance().registerFunction(&serial_readln, "serialRead");
    chaiscript_gateway::Instance().registerFunction(&serial_close, "serialClose");
    chaiscript_gateway::Instance().registerFunction(&update_gps_location, "updateGPS");

    JSTest jsTest;
    jsTest.testAllTheThings();
/*
    ContextTest contextTest;
    contextTest.testAllTheThings();

    EventCallbackTest eventBusTest;
    eventBusTest.testAllTheThings();

    ProcessTest sse;
    sse.testAllTheThings();
    */
}
