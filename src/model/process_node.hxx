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
#include "context.hxx"

using namespace std;

enum class ProcessNodeT {
    serviceTask, intermediateCatchEvent, exclusiveGateway, startEvent, endEvent, signalEvent
};

class ProcessNode {
    friend class Process;
    ProcessNodeT elementType;
    std::string outgoingSequenceId;

protected:
    std::string id;

public:
    ProcessNode(ProcessNodeT t) : elementType(t) {}

    ProcessNode(ProcessNodeT t, string idarg):id(idarg), elementType(t) {}

    void setOutgoingNodeId(std::string seq) {
        outgoingSequenceId = seq;
    }

    void setId(const char* idarg) {
        id = idarg;
    }

    void setId(string idarg) {
        id = idarg;
    }

    std::string getId() {
        if (id.length() < 1) {
            id = "NA";
        }
        return id;
    };

    ProcessNodeT getProcessNodeType() {
        return elementType;
    }

    bool matches(string idarg) {
        return getId() == idarg;
    }

    virtual std::string getNextNodeId() {
        return outgoingSequenceId;
    };
};

using ProcessNodePtr = shared_ptr<ProcessNode>;

class ServiceTask: public ProcessNode {
    std::string functionName;
    std::vector<std::string> paramNames;

public:
    ServiceTask() : ProcessNode(ProcessNodeT::serviceTask) {}
    void execute();
};


using GatewayFlow = pair<std::string, std::string>;
class ExclusiveGateway: public ProcessNode {
    std::vector<GatewayFlow> flows;

public:
    ExclusiveGateway(std::string name) : ProcessNode(ProcessNodeT::exclusiveGateway, name) {}

    void addFlow(std::string script, std::string nodeId) {
        flows.push_back(GatewayFlow(script, nodeId));
    }

    std::string getNextNodeId() {
        if (flows.size() < 1) {
            return ProcessNode::getNextNodeId();
        }
        for (auto iter = flows.begin() ; iter != flows.end(); ++iter) {
           if (Context::Instance().evaluate_js_condition(iter->first)) {
               return iter->second;
           }
        }
        return nullptr;
    };
};

using ExclusiveGatewayPtr = shared_ptr<ExclusiveGateway>;


#endif //GPM_PROCESSMODEL_H
