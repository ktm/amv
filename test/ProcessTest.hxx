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
    }
};

#endif //AMVMODEL_SIMPLESTARTEVENTS_H
