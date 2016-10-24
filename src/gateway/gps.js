"use strict";

/**
 * Created by ktm on 9/3/16.
 */
const state = require("../state");

const five = require("johnny-five");

exports.initGPS = function() {
    if ( (state.gpsReady) || (!state.boardReady)) {
        return;
    }
    state.gpsReady = true;
    var gps = new five.GPS({
        breakout: "ADAFRUIT_ULTIMATE_GPS",
        pins: {
            rx: 11,
            tx: 10,
        },
        frequency: .1,   //  "$PMTK220," + String(1000 / state.frequency)
    });

    gps.on("change", function() {
        state.globalState.currentLocation.lat = this.latitude;
        state.globalState.currentLocation.long = this.long;
    });

    gps.on("navigation", function() {
        state.globalState.currentHeading = this.course;
        state.globalState.currentSpeed = this.speed;
    });
};
