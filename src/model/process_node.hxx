//
// Created by ktm on 5/22/15.
//

#ifndef GPM_PROCESSMODEL_H
#define GPM_PROCESSMODEL_H

#include <algorithm>
#include <string>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

const char* DEFAULT_SEQUENCE = "default";

using NameValuePair = pair<string, string>;
using NameValuePairPtr = shared_ptr<NameValuePair>;

struct SequenceConditionPair {
    SequenceConditionPair(string a, string b) : targetElementId(a),condition(b) {}
    string targetElementId;
    string condition;
};

using SequenceConditionPairPtr = shared_ptr<SequenceConditionPair>;

enum class ProcessNodeT {
    serviceTask, intermediateCatchEvent, exclusiveGateway, startEvent, endEvent, signalEvent
};

class ProcessNode {
    friend class Process;
    ProcessNodeT elementType;

protected:
    std::string id;

    std::list<SequenceConditionPairPtr> incomingSequenceList;
    std::list<SequenceConditionPairPtr> outgoingSequenceList;

public:
    ProcessNode(ProcessNodeT t) {
        setProcessNodeType(t);
    }

    void setProcessNodeType(ProcessNodeT arg) {
        elementType = arg;
    }

    void setId(const char* idarg) {
        id = idarg;
    }

    std::string getId() {
        if (id.length() < 1) {
            id = "NA";
        }
        return id;
    };

    void addIncomingSequence(const char* id) {
        addIncomingSequence(id, DEFAULT_SEQUENCE);
    }

    void addIncomingSequence(const char* id, const char* condition) {
        incomingSequenceList.push_back(make_shared<SequenceConditionPair >(id, condition));
    }

    void addOutgoingSequence(const char* id, const char* condition) {
        outgoingSequenceList.push_back(make_shared<SequenceConditionPair >(id, condition));
    }

    void addOutgoingSequence(const char* id) {
        addOutgoingSequence(id, DEFAULT_SEQUENCE);
    }

    ProcessNodeT getProcessNodeType() {
        return elementType;
    }
};

using ProcessNodePtr = shared_ptr<ProcessNode>;


class ServiceTask: public ProcessNode {
    std::string functionCall;
    std::string argname;

public:
    ServiceTask() : ProcessNode(ProcessNodeT::serviceTask) {}
};

class ExclusiveGateway: public ProcessNode {
public:
    ExclusiveGateway() : ProcessNode(ProcessNodeT::exclusiveGateway) {}
};


#endif //GPM_PROCESSMODEL_H
