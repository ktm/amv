//
// Created by ktm on 8/14/15.
//

#define TEST

#include "ProcessTest.hxx"
#include "ContextTest.hxx"
#include "EventCallbackTest.h"
#include "jstest.h"

int main() {
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
