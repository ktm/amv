//
// Created by ktm on 12/26/15.
//

#ifndef AMVMODEL_JAVASCRIPT_H
#define AMVMODEL_JAVASCRIPT_H

#include "../src/serial/serial.h"

std::string fxn() {
    return "Hello World!";
}

class JSTest {
    int gpsFD;
public:
    JSTest() { }

    void testAllTheThings() {
        cout << "JSTest testAllTheThings begin..." << endl;
        testConfig();
//        testContext();
        cout << "JSTest testAllTheThings end..." << endl;
    }

    void testConfig() {
        cout << "testConfind begin..." << endl;

        Context::Instance().write("gpsPort", "/dev/ttyUSB0");
        gpsFD = chaiscript_gateway::Instance().call<int>("serialInit", "gpsPort");

        assert(gpsFD > 0);

        cout << "testConfind end..." << endl;
    }

    void testContext() {
        cout << "testContext begin..." << endl;

        Process* p = new Process("anonymousStartEvent");
        StartEvent* se = new StartEvent("start");
        se->addNVP("nvp1", "testVal");
        p->addProcessNode(StartEventPtr(se));

        p->start("start");

        Context& c1 = Context::Instance();
        string xval = c1.read("nvp1");
        assert(xval.compare("testVal") == 0);

//        bool jscontext = Context::Instance().js_context.eval<bool>("nvp1 == \"testVal\"");
//        assert(jscontext);

//        jscontext = Context::Instance().js_context.eval<bool>("nvp1 == \"XXtestVal\"");
//        assert(!jscontext);

        cout << "testContext passed" << endl;
    }

};
#endif //AMVMODEL_JAVASCRIPT_H
