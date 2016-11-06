/**
 * Created by ktm on 9/21/16.
 */
"use strict";

var math = require('mathjs');

function radians(degrees) {
    var pix = math.PI / 180;
    return degrees * pix;
}

function degrees(radians) {
    return radians * (180.0 / math.PI);
}

exports.calculateHeading = function (lat1, long1, lat2, long2, currentHeading) {
    return deltaCourse(currentHeading, courseTo(lat1, long1, lat2, long2));
};

// below are adapted from https://github.com/mikalhart/TinyGPSPlus
function courseTo(lat1, long1, lat2, long2) {
// returns course in degrees (North=0, West=270) from position 1 to position 2,
// both specified as signed decimal-degrees latitude and longitude.
// Because Earth is no exact sphere, calculated course may be off by a tiny fraction.
// Courtesy of Maarten Lamers

    var dlon = radians(long2-long1);
    lat1 = radians(lat1);
    lat2 = radians(lat2);

    var a1 = math.sin(dlon) * math.cos(lat2);

    var a2 = math.sin(lat1) * math.cos(lat2) * math.cos(dlon);
    a2 = math.cos(lat1) * math.sin(lat2) - a2;
    a2 = math.atan2(a1, a2);
    if (a2 < 0.0) {
        a2 += math.PI * 2;
    }

    return degrees(a2);
}

function deltaCourse(currentCourse, newCourse) {
    return (360 + newCourse - currentCourse) % 360;
}

exports.distanceBetween = function(lat1, long1, lat2, long2) {
    // returns distance in meters between two positions, both specified
    // as signed decimal-degrees latitude and longitude. Uses great-circle
    // distance computation for hypothetical sphere of radius 6372795 meters.
    // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
    // Courtesy of Maarten Lamers
    var delta = radians(long1-long2);
    var sdlong = math.sin(delta);
    var cdlong = math.cos(delta);
    lat1 = radians(lat1);
    lat2 = radians(lat2);
    var slat1 = math.sin(lat1);
    var clat1 = math.cos(lat1);
    var slat2 = math.sin(lat2);
    var clat2 = math.cos(lat2);
    delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
    delta = math.square(delta);
    delta += math.square(clat2 * sdlong);
    delta = math.sqrt(delta);
    var denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
    delta = math.atan2(delta, denom);
    return delta * 6372795;
};


exports.calculateCourseChange = function(currentCourse, newCourse) {
    var courseChangeNeeded = (360 + newCourse - currentCourse) % 360;
    return courseChangeNeeded;
}
