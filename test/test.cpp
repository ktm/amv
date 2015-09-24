//
// Created by ktm on 8/14/15.
//

#define TEST

#include "ProcessTest.hxx"
#include "ContextTest.hxx"

int main() {
    ProcessTest * sse = new ProcessTest();
    sse->testAllTheThings();

    ContextTest* contextTest = new ContextTest();
    contextTest->testAllTheThings();
}
