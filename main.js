#!/usr/bin/env node

const bpmn = require('bpmn');

bpmn.createUnmanagedProcess(__dirname + '/bpmn/navigate.bpmn', function(err, myProcess){
    myProcess.triggerEvent("NavigateStartEvent");
});
