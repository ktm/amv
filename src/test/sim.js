/**
 * Created by ktm on 10/14/16.
 */

"use strict";
const simstate = require("./sim.json");
const state = require("./../state");


exports.run = function() {
    var counter = 0;

    var interval = setInterval( function() {
        state.globalState.setLat(simstate[counter].currentLocation.lat);
        state.globalState.setLong(simstate[counter].currentLocation.long);
        state.globalState.setDestination(simstate[counter].destination);
        state.globalState.setHeading(simstate[counter].currentHeading);
        counter++;
        if (counter == simstate.length) {
            clearInterval(interval);
        }
        // read a line from sim.json
        // post state updates
    }, 10000);
};