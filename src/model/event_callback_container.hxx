//
// Created by ktm on 9/25/15.
//

#ifndef AMVMODEL_EVENTBUS_HXX
#define AMVMODEL_EVENTBUS_HXX

#include <algorithm>
#include <map>
#include <mutex>
#include <iostream>
#include "../collection/name_value_pair.hxx"

using EventCallback = function<void(NameValuePairPtr)>;
using EventCallbackMMap = std::multimap<std::string, EventCallback>;

class EventCallbackContainer {
private:
    std::mutex data_mutex;
    EventCallbackMMap callbackMap;

public:
    EventCallbackContainer(){}

    void addCallback(std::string name, EventCallback cb) {
        callbackMap.emplace(name, cb);
    }

    void fireEvent(std::string name, NameValuePairPtr nvp) {
        std::pair <EventCallbackMMap::iterator, EventCallbackMMap::iterator> callbackRange;
        callbackRange = callbackMap.equal_range(name);
        for_each (callbackRange.first, callbackRange.second, [nvp](EventCallbackMMap::value_type x){x.second(nvp);});
    }
};


#endif //AMVMODEL_EVENTBUS_HXX
