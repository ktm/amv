/**
 * Created by ktm on 8/27/16.
 */

const bpmn = require('bpmn');

exports.run = function() {
    bpmn.createUnmanagedProcess(__dirname + "/bpmn/mission/missionLoop.bpmn", function(err, myProcess){
        myProcess.triggerEvent("startMissionEvent");
    });

    bpmn.createUnmanagedProcess(__dirname + "/bpmn/navigate.bpmn", function(err, myProcess){
        myProcess.triggerEvent("NavigateStartEvent");
    });

    bpmn.createUnmanagedProcess(__dirname + "/bpmn/observe.bpmn", function(err, myProcess){
        myProcess.triggerEvent("StartEvent");
    });

}

