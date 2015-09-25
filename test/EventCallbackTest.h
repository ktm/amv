//
// Created by ktm on 9/25/15.
//

#ifndef AMVMODEL_EVENTBUS_H
#define AMVMODEL_EVENTBUS_H

#include <iostream>

#include "../src/collection/name_value_pair.hxx"
#include "../src/model/event_callback_container.hxx"

class EventCallbackTest {

public:
    EventCallbackTest() { }

    void testAllTheThings() {
        testCallback();
    }

    void testCallback() {
        EventCallbackContainer * eb = new EventCallbackContainer();
        static bool callbackFired = false;

        eb->addCallback("testcb", [](NameValuePairPtr nvp){
            callbackFired = true;
        });

        NameValuePairPtr nvp = make_shared<NameValuePair> ("x", "xyz");
        eb->fireEvent("testcb", nvp);
        assert(callbackFired);

        callbackFired = false;
        eb->fireEvent("X", nvp);
        assert(!callbackFired);
    }

};
#endif //AMVMODEL_EVENTBUS_H
