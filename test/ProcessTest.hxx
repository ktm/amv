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

    void testAllTheThings() {
        testContext();
        testStartEvent();
        testCatchSignal();
    }

    void testContext() {
        cout << "testContext begin..." << endl;
        Process* p = new Process("anonymousStartEvent");
        StartEvent* se = new StartEvent("start");
        se->addNVP("nvp1", "testVal");
        p->addProcessNode(StartEventPtr(se));

        StartEventPtr testEvent(new StartEvent("start"));
        p->onStartEvent(testEvent);

        assert(p->currentNode->getId().compare("start") == 0);
        cout << "testContext passed" << endl;
    }

    void testStartEvent() {
        cout << "testStartEvent begin..." << endl;
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

    void testCatchSignal() {
        cout << "testCatchSignal started..." << endl;
        Process* p = new Process("anonymousStartSignal");
        EndEvent* endEvent = new EndEvent("end");
        SignalEvent* signalEvent = new SignalEvent("SIG1");
        StartEvent* se = new StartEvent("start");

        se->addOutgoingSequence("SIG1");
        signalEvent->addOutgoingSequence("end");

        p->addProcessNode(StartEventPtr(se));
        p->addProcessNode(EndEventPtr(endEvent));
        p->addProcessNode(SignalPtr(signalEvent));
        StartEventPtr testEvent(new StartEvent("start"));
        p->onStartEvent(testEvent);
        EventCallbackContainer::Instance().fireEvent("SIG1");
        this_thread::sleep_for(2s);

        assert(p->currentNode->getId().compare("end") == 0);
        assert(p->lifecycleState==ProcessLifecycle::stopped);
        cout << "testCatchSignal passed." << endl;
    }
};

#endif //AMVMODEL_SIMPLESTARTEVENTS_H
