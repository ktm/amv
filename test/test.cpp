//
// Created by ktm on 8/14/15.
//

#define TEST

#include "ProcessTest.hxx"
#include "ContextTest.hxx"
#include "EventCallbackTest.h"

int main() {
    ProcessTest sse;
    sse.testAllTheThings();

    ContextTest contextTest;
    contextTest.testAllTheThings();

    EventCallbackTest eventBusTest;
    eventBusTest.testAllTheThings();
}
