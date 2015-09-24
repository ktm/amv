//
// Created by ktm on 9/11/15.
//

#ifndef AMVMODEL_CONTEXTTEST_H
#define AMVMODEL_CONTEXTTEST_H

#include <assert.h>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>

#include "../src/model/context.hxx"

class ContextTest {

public:
    ContextTest(){ }

    void testAllTheThings() {
        /*
        testSingleton();
        testSingleSetAndGet("test", "frog");
        testSingleUpdate();
        */
        testMultipleSetAndGet();
    }

    void testSingleton() {
        Context& c1 = Context::Instance();
        Context& c2 = Context::Instance();

        assert(&c2 == &c1);
        cout << "testSingleton passed" << endl;
    }

    static void testSingleUpdate() {

        Context& c1 = Context::Instance();
        c1.write("test", "frog");
        string xval = c1.read("test");
        assert(xval.compare("frog") == 0);

        c1.write("test", "pig");
        xval = c1.read("test");
        assert(xval.compare("pig") == 0);

        cout << "testSingleUpdate passed" << endl;
    }

    static void testSingleSetAndGet(string name, string val) {
        Context& c1 = Context::Instance();
        c1.write(name, val);
        string xval = c1.read(name);
        assert(xval.compare(val) == 0);
        cout << "testSingleSetAndGet passed" << endl;
    }

    static void call_from_thread(std::chrono::system_clock::time_point time_point) {
        using std::chrono::system_clock;

        cout << "sleeping..." << endl;
        std::this_thread::sleep_until(time_point);
        cout << "... done sleeping" << endl;
        Context::Instance().write("Bxyz", "xxx");
        Context::Instance().write("Axyz", "pdq");
        Context::Instance().read("Bxyz");
        Context::Instance().read("Cx");
        cout << "... done with thread" << endl;
    }

    static void punk_thread() {
        cout << "punking..." << endl;
        for (int i=0; i<3000000; i++) {
            Context::Instance().write("Bxyz", "123");
            Context::Instance().write("Axyz", "555");
        }
        cout << "... done punking" << endl;
    }

    void testMultipleSetAndGet() {
        cout << "hardware concurrency: " << std::thread::hardware_concurrency() << endl;
        std::chrono::system_clock::time_point soon = std::chrono::system_clock::now() + std::chrono::seconds(5);

        std::thread t1(call_from_thread, soon);
        std::thread t2(call_from_thread, soon);
        std::thread t3(call_from_thread, soon);
        std::thread t4(call_from_thread, soon);
        std::thread t5(call_from_thread, soon);
        std::thread t6(punk_thread);

        t6.join();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
    }
};
#endif //AMVMODEL_CONTEXTTEST_H