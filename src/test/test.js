"use strict";

const config = require("./config.json");
const maneuver = require("../gateway/maneuver");
const missionProcess = require(config.mission);
const state = require("./../state");
const sim = require("./sim.js");

maneuver.initManeuverListener();
state.globalState.setDestination(config.destination);
missionProcess.run();
sim.run();

