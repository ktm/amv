"use strict";
var state = require("../state");
const navHelper = require("../helper/navigation");

function NavigateStartEvent(error, done) {
    done();
}

exports.NavigateStartEvent = NavigateStartEvent;
function defaultEventHandler(eventType, currentFlowObjectName, handlerName, reason, done) {
    done();
}
exports.defaultEventHandler = defaultEventHandler;

function defaultErrorHandler(error, done) {
    // Called if errors are thrown in the event handlers
    done();
}
exports.defaultErrorHandler = defaultErrorHandler;

function AdjustCourse(data, done) {
    if (changeCourse) {
        var lat1 = state.globalState.currentLocation.lat;
        var long1 = state.globalState.currentLocation.long;

        var lat2 = state.globalState.currentDestination.lat;
        var long2 = state.globalState.currentDestination.long;

        var newHeading = navHelper.calculateHeading(lat1, long1, lat2, long2, state.globalState.currentHeading);
        var newDistance = navHelper.distanceBetween(lat1, long1, lat2, long2);
        if (newDistance > 100) {
            var courseChange = navHelper.calculateCourseChange(state.globalState.currentHeading,newHeading);
            state.missionEventEmitter.emit("steer", courseChange);
        }
    }
    done(data);
}
exports.AdjustCourse = AdjustCourse;

var changeCourse = true;
function checkLocation(data, done) {
    changeCourse = !state.globalState.currentDestination.withinRange(state.globalState.currentLocation, state.globalState.navigationResolution);
    done(data);
}
exports.checkLocation = checkLocation;

function keepGoing$yes(data) {
    return true;
}
exports.keepGoing$yes = keepGoing$yes;

function keepGoing$no(data) {
    return false;
}
exports.keepGoing$no = keepGoing$no;

function navTimer$getTimeout(data, done) {
    return state.globalState.navTimer;
}
exports.navTimer$getTimeout = navTimer$getTimeout;

