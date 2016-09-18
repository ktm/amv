"use strict";
var Location = (function () {
    function Location(lat, long) {
        this.lat = lat;
        this.long = long;
    }
    Location.prototype.withinRange = function (rhs, rangeInMeters) {
        return false;
    };
    return Location;
}());
exports.Location = Location;
var MissionPhase = (function () {
    function MissionPhase() {
    }
    MissionPhase.outbound = "outbound";
    MissionPhase.inbound = "inbound";
    MissionPhase.onstation = "onstation";
    return MissionPhase;
}());
var State = (function () {
    function State() {
        this.navTimer = 15000;
        this.navigationResolution = 10;
        this.missionLoopTimer = 3000;
        this.observationTimer = 500;
        this.inactiveTimer = 3000;
        this.currentLocation = new Location(0, 0);
        this.currentDestination = new Location(0, 0);
        this.currentCourse = 0;
        this.currentSpeed = 0;
        this.missionTime = Date.now();
        this.boardReady = false;
        this.gpsReady = false;
    }
    State.prototype.setLat = function (arg) {
        this.currentLocation.lat = arg;
    };
    State.prototype.setLong = function (arg) {
        this.currentLocation.long = arg;
    };
    State.prototype.isOnStation = function () {
        if (this.missionPhase) {
            return this.missionPhase === MissionPhase.onstation;
        }
        return false;
    };
    return State;
}());
exports.globalState = new State();