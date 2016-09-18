"use strict";
var state_1 = require("../../state");
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
function startMission(data, done) {
    done(data);
}
exports.startMission = startMission;
;
function updateMission(data, done) {
    console.log("   updateMission " + (Date.now() - state_1.globalState.missionTime));
    done(data);
}
exports.updateMission = updateMission;
;
function missionGateway$missionComplete(data) {
    return false;
}
exports.missionGateway$missionComplete = missionGateway$missionComplete;
;
function missionGateway$missionContinue(data) {
    return true;
}
exports.missionGateway$missionContinue = missionGateway$missionContinue;
;
function missionLoopTimer$getTimeout(data, done) {
    return state_1.globalState.missionLoopTimer;
}
exports.missionLoopTimer$getTimeout = missionLoopTimer$getTimeout;
;
//# sourceMappingURL=missionLoop.js.map