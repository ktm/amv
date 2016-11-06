"use strict";

const config = require("./config.json");
const missionProcess = require(config.mission);
const state = require("./../state");

const sim = require("./sim.js");

state.globalState.setDestination(config.destination);

state.missionEventEmitter.on('steer', (courseChange) => {
    console.log('steer event received');

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

missionProcess.run();
sim.run();
