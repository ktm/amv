//
// Created by ktm on 8/14/15.
//

#define TEST

#include "ProcessTest.hxx"
#include "ContextTest.hxx"
#include "EventCallbackTest.h"

int main() {
    ContextTest contextTest;
    contextTest.testAllTheThings();

    EventCallbackTest eventBusTest;
    eventBusTest.testAllTheThings();

    ProcessTest sse;
    sse.testAllTheThings();
}
