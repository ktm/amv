"use strict"

const config = require('./config.json');
const missionProcess = require(config.mission);


const state = require('./state');
const five = require('johnny-five');

var board = new five.Board({ port: config.johnnyFivePort });

board.on("ready", function() {
    state.boardReady = true;
    console.log("board ready");
    missionProcess.run();
});

