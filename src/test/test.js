"use strict";

const config = require("./config.json");
const missionProcess = require(config.mission);
const state = require("./../state");

const sim = require("./sim.js");

state.globalState.setDestination(config.destination);
missionProcess.run();
sim.run();
