/**
 * Created by ktm on 10/14/16.
 */

"use strict";
const simstate = require("./sim.json");
const state = require("./../state");


exports.run = function() {
    var counter = 0;

    var interval = setInterval( function() {
        console.log("sim interval: " + counter);
        state.globalState.setLat(simstate[counter].currentLocation.lat);
        state.globalState.setLong(simstate[counter].currentLocation.long);
        state.globalState.setDestination(simstate[counter].destination);
        state.globalState.setHeading(simstate[counter].currentHeading);
        counter++;
        if (counter == simstate.length) {
            clearInterval(interval);
            console.log("sim complete");
        }
    }, 10000);
};