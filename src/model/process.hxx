//
// Created by ktm on 8/22/15.
//

#ifndef AMVMODEL_PROCESS_H
#define AMVMODEL_PROCESS_H

#include "context.hxx"
#include "event.hxx"
#include "process_node.hxx"
#include "../collection/name_value_pair.hxx"

#include <algorithm>
#include <list>
#include <map>
#include <string>

#ifdef TEST
#include "../../test/ProcessTest.hxx"
#endif

/** \enum ProcessLifecycle
 *  \brief Lifecycles of a process
 *  \details These are the details
 *
 */
enum class ProcessLifecycle {
    instantiated, started, running, stopped
};

/** \class Process
 *  \brief The composition and execution of a single process
 *  \details TBD
 *
 */
class Process {
#ifdef TEST
    friend class ProcessTest;
#endif
    std::string processName;

    std::map<std::string, ProcessNodePtr> processNodeMap;

    ProcessNodePtr currentNode;

    ProcessLifecycle lifecycleState;

protected:
    ProcessNodePtr findNode(ProcessNodeT elementT, string elementName) {
        auto list = find_if(processNodeMap.begin(), processNodeMap.end(),
                            [elementT, elementName](const pair<string, ProcessNodePtr>&r) {
                                return ((r.first.compare(elementName) == 0) ? elementT== r.second->getProcessNodeType() : false);
                            });
        if (list == processNodeMap.end()) {
            return nullptr;
        }

        return list->second;
    }

   ProcessNodePtr findNode(string elementId) {
        auto list = find_if(processNodeMap.begin(), processNodeMap.end(),
                            [elementId](const pair<string, ProcessNodePtr>&r) {
                                return ((r.first.compare(elementId) == 0));
                            });
        if (list == processNodeMap.end()) {
            return nullptr;
        }

        return list->second;
    }

    void updateContext(string name, string value) {
        Context::Instance().write(name, value);
    }

    void executeNode(ProcessNodePtr node) {
        currentNode = node;
        ProcessNodePtr nextNode = nullptr;
        switch (node->getProcessNodeType()) {
            case ProcessNodeT::startEvent: {
                // FIXME can't figure out how to dynamic_pointer_cast this:
                StartEvent* se = (StartEvent *) node.get();

                for (const NameValuePairPtr nvp : se->nvpList) {
                    updateContext(nvp->first, nvp->second);
                }
                break;
            }
            case ProcessNodeT::endEvent: {
                // FIXME can't figure out how to dynamic_pointer_cast this:
                onEndEvent(EndEventPtr((EndEvent *) node.get()));
                break;
            }
        }

        if (currentNode->outgoingSequenceList.size() == 1) {
            std::list<SequenceConditionPairPtr> l = currentNode->outgoingSequenceList;
            SequenceConditionPairPtr x = l.front();
            nextNode = findNode(currentNode->outgoingSequenceList.front()->targetElementId);
        } else if (currentNode->outgoingSequenceList.size() > 1) {
            nextNode = evaluateNextNode(currentNode);
        }

        if (nextNode != nullptr) {
            executeNode(nextNode);
        }
    }

    ProcessNodePtr evaluateNextNode(ProcessNodePtr node) {
        ProcessNodePtr retval = nullptr;
        return retval;
    }

public:
    Process(const char* idarg): processName(idarg), lifecycleState(ProcessLifecycle::instantiated) {}

    void addProcessNode(ProcessNodePtr node) {
        processNodeMap.emplace(node->getId(), node);
    }

    void onStartEvent(StartEventPtr event) {
        // find node
        auto node = findNode(event->getProcessNodeType(), event->getEventName());

        if (node != nullptr) {
            lifecycleState = ProcessLifecycle::started;
            executeNode(node);
        }
    }

    void onEndEvent(EndEventPtr event) {
        lifecycleState = ProcessLifecycle::stopped;
    }

    void onContextChangeEvent(ContextEventPtr event);
    void catchSignal(SignalPtr event);
};

#endif //AMVMODEL_PROCESS_H
