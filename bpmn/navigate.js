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


var loop = 0;

exports.AdjustCourse = function(data) {
    // has to return true or false
    // the name of the sequence flow follows after "$".
    // if there is no name, an error is thrown
    console.log("AdjustCourse " + loop);

    done(data);
};

exports.keepGoing$yes = function(data) {
    // has to return true or false
    // the name of the sequence flow follows after "$".
    // if there is no name, an error is thrown
    console.log("keepGoing " + loop);
    loop = loop + 1;
    return loop < 5;
};

exports.keepGoing$no = function(data) {
    // has to return true or false
    // the name of the sequence flow follows after "$".
    // if there is no name, an error is thrown
    console.log("stop");
    return loop == 5;
};

exports.navTimer$getTimeout = function(data, done) {
    // called when arriving on "Intermediate Catch Timer Event"
    // should return wait time in ms.
    console.log("navTimer getTimeout");

    return 3000;
};
