//
// Created by ktm on 12/26/15.
//

#ifndef AMVMODEL_JAVASCRIPT_H
#define AMVMODEL_JAVASCRIPT_H

#include "../src/javascript/duktape.h"

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
        duk_context *ctx = Context::Instance().jsctx();
        duk_eval_string(ctx, "print('Hello world!');");
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

        duk_context *ctx = Context::Instance().jsctx();

        duk_eval_string(ctx, "test_val = nvp1;");
        duk_get_global_string(ctx, "test_val");
        const char* test_val = duk_get_string(ctx, 1);
        string c("testVal");
        assert(c.compare(test_val) == 0);

        cout << "testContext passed" << endl;
    }

};
#endif //AMVMODEL_JAVASCRIPT_H
