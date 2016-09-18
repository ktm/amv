"use strict";
var state_1 = require("../state");
function defaultEventHandler(eventType, currentFlowObjectName, handlerName, reason, done) {
    done();
}
exports.defaultEventHandler = defaultEventHandler;
;
function defaultErrorHandler(error, done) {
    // Called if errors are thrown in the event handlers
    console.log("defaultErrorHandler " + error);
    done();
}
exports.defaultErrorHandler = defaultErrorHandler;
;
function report(data, done) {
    console.log("         Observe report " + (Date.now() - state_1.globalState.missionTime));
    done(data);
}
exports.report = report;
;
function keepGoing$yes(data) {
    return true;
}
exports.keepGoing$yes = keepGoing$yes;
;
function keepGoing$no(data) {
    return false;
}
exports.keepGoing$no = keepGoing$no;
;
function cvTimer$getTimeout(data, done) {
    if (state_1.globalState.isOnStation()) {
        return state_1.globalState.observationTimer;
    }
    return state_1.globalState.inactiveTimer;
}
exports.cvTimer$getTimeout = cvTimer$getTimeout;
;
//# sourceMappingURL=observe.js.map