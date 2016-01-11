//
// Created by ktm on 12/26/15.
//

#ifndef AMVMODEL_JAVASCRIPT_H
#define AMVMODEL_JAVASCRIPT_H

#include <chaiscript/chaiscript.hpp>

std::string fxn() {
    return "Hello World!";
}


class JSTest {
public:
    JSTest() { }

    void testAllTheThings() {
        cout << "JSTest testAllTheThings begin..." << endl;
        testConfig();
        testContext();
        cout << "JSTest testAllTheThings end..." << endl;
    }

    void testConfig() {
        cout << "testConfind begin..." << endl;
        Context::Instance().js_context.add(chaiscript::fun(&fxn), "fxn");

        std::string d = Context::Instance().js_context.eval<std::string>("fxn();");
        cout << d << endl;
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

        bool jscontext = Context::Instance().js_context.eval<bool>("nvp1 == \"testVal\"");
        assert(jscontext);

        jscontext = Context::Instance().js_context.eval<bool>("nvp1 == \"XXtestVal\"");
        assert(!jscontext);

        cout << "testContext passed" << endl;
    }

};
#endif //AMVMODEL_JAVASCRIPT_H
