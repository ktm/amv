"use strict";

/**
 * Created by ktm on 9/3/16.
 */
const state = require('../state');

const five = require('johnny-five');

exports.initGPS = function() {
    if ( (state.gpsReady) || (!state.boardReady)) {
        return;
    }
    state.gpsReady = true;
    console.log("initGPS");
    var gps = new five.GPS({
        breakout: "ADAFRUIT_ULTIMATE_GPS",
        pins: {
            rx: 11,
            tx: 10,
        },
        frequency: .1,   //  "$PMTK220," + String(1000 / state.frequency)
    });
    // If latitude, longitude change log it
    gps.on("change", function() {
        console.log("GPS change " + new Date());
        state.globalState.currentLocation.lat = this.latitude;
        state.globalState.currentLocation.long = this.long;
    });
    // If speed, course change log it
    gps.on("navigation", function() {
        state.globalState.currentCourse = this.course;
        state.globalState.currentSpeed = this.speed;
    });
};
