/**
 * Created by ktm on 9/15/16.
 */

"use strict";

const state = require('../state');
const Location = require('../state').Location;
const five = require('johnny-five');

exports.initSteering = function() {
    if (!state.boardReady) {
        return;
    }
    new five.Servo({
        pin: 9,
        range: [45, 135],
        startAt: 90,

    });

    servo.center();
};
