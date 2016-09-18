"use strict";
var state_1 = require("../state");
var gps_1 = require("../gateway/gps");
var maneuver_1 = require("../gateway/maneuver");

function NavigateStartEvent(error, done) {
    gps_1.initGPS();
    maneuver_1.initSteering();
    done();
}
exports.NavigateStartEvent = NavigateStartEvent;
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
function AdjustCourse(data, done) {
    console.log("adujsting course");
    done(data);
}
exports.AdjustCourse = AdjustCourse;
;
var changeCourse = true;
function checkLocation(data, done) {
    changeCourse = !state_1.globalState.currentDestination.withinRange(state_1.globalState.currentLocation, state_1.globalState.navigationResolution);
    console.log("checkLocation.  change course: " + changeCourse + " " + (Date.now() - state_1.globalState.missionTime));
    done(data);
}
exports.checkLocation = checkLocation;
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
function navTimer$getTimeout(data, done) {
    return state_1.globalState.navTimer;
}
exports.navTimer$getTimeout = navTimer$getTimeout;
;
//# sourceMappingURL=navigate.js.map