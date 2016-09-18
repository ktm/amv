import{State} from "../state.js";

exports.defaultEventHandler = function(eventType, currentFlowObjectName, handlerName, reason, done) {
    // Called, if no handler could be invoked.
    console.log("defaultEventHandler " + currentFlowObjectName);
    done();
};

exports.defaultErrorHandler = function(error, done) {
    // Called if errors are thrown in the event handlers
    console.log("defaultErrorHandler " + error);
    done();
};

exports.AdjustCourse = function(data, done) {
    done(data);
};


exports.checkLocation = function(data, done) {
    console.log("checkLocation ");

    done(data);
};


exports.keepGoing$yes = function(data) {
    return true;
};

exports.keepGoing$no = function(data) {
    return false;
};

exports.navTimer$getTimeout = function(data, done) {
    return 3000;
};
