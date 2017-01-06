/**
 * Created by ktm on 9/15/16.
 */

"use strict";

const state = require("../state");
const five = require("johnny-five");

var escLeft = null;
var escRight = null;
var listenerReady = false;

exports.initSteering = function() {
    if (!state.boardReady) {
        return;
    }

    escLeft = new five.ESC(9);
    escRight = new five.ESC(10);

    escLeft.min();
    escRight.min();
};

exports.initManeuverListener = function () {
    if (listenerReady) {
        return;
    }

    state.missionEventEmitter.on('steer', (courseChange) => {
        if (courseChange >= 345 || courseChange < 15) {
// go straight
            console.log('go straight');
        } else if (courseChange >= 315 && courseChange < 345) {
// a little to the left
            console.log('slight left');
        }
        else if (courseChange >= 15 && courseChange < 45)
            console.log('slight right');
        else if (courseChange >= 255 && courseChange < 315)
            console.log('hard left');
        else if (courseChange >= 45 && courseChange < 105)
            console.log('hard right');
        else
            console.log('about face!');
    });

    listenerReady = true;
};


