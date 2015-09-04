//
// Created by ktm on 8/14/15.
//

#ifndef AMVMODEL_SIMPLESTARTEVENTS_H
#define AMVMODEL_SIMPLESTARTEVENTS_H


#include <assert.h>
#include "../src/model/process.hxx"
#include "../src/model/process_node.hxx"
#include "../src/model/event.hxx"

class ProcessTest {

public:
    ProcessTest(){}

    void testContext() {
        Process* p = new Process("anonymousStartEvent");
        StartEvent* se = new StartEvent("start");
        se->addNVP("nvp1", "testVal");
        p->addProcessNode(StartEventPtr(se));

        StartEventPtr testEvent(new StartEvent("start"));
        p->onStartEvent(testEvent);

        assert(p->currentNode->getId().compare("start") == 0);
        cout << "testContext did not fail, but context is not yet implemented." << endl;
    }

    void testStartEvent() {
        Process* p = new Process("anonymousStartEvent");
        EndEvent* endEvent = new EndEvent("end");
        StartEvent* se = new StartEvent("start");
        se->addOutgoingSequence("end");

        p->addProcessNode(StartEventPtr(se));
        p->addProcessNode(EndEventPtr(endEvent));

        StartEventPtr testEvent(new StartEvent("start"));
        p->onStartEvent(testEvent);

        assert(p->currentNode->getId().compare("end") == 0);
        assert(p->lifecycleState==ProcessLifecycle::stopped);
        cout << "testStartEvent passed." << endl;
    }

};

#endif //AMVMODEL_SIMPLESTARTEVENTS_H
