/**
 * Created by ktm on 9/21/16.
 */
"use strict";

function radians(degrees) {
    var pix = Math.PI / 180;
    return degrees * pix;
}

function degrees(radians) {
    return radians * (180.0 / Math.PI);
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

    var a1 = Math.sin(dlon) * Math.cos(lat2);

    var a2 = Math.sin(lat1) * Math.cos(lat2) * Math.cos(dlon);
    a2 = Math.cos(lat1) * Math.sin(lat2) - a2;
    a2 = Math.atan2(a1, a2);
    if (a2 < 0.0) {
        a2 += Math.PI * 2;
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
    var sdlong = Math.sin(delta);
    var cdlong = Math.cos(delta);
    lat1 = radians(lat1);
    lat2 = radians(lat2);
    var slat1 = Math.sin(lat1);
    var clat1 = Math.cos(lat1);
    var slat2 = Math.sin(lat2);
    var clat2 = Math.cos(lat2);
    delta = (clat1 * slat2) - (slat1 * clat2 * cdlong);
    delta = Math.sqr(delta);
    delta += Math.sqr(clat2 * sdlong);
    delta = Math.sqrt(delta);
    var denom = (slat1 * slat2) + (clat1 * clat2 * cdlong);
    delta = Math.atan2(delta, denom);
    return delta * 6372795;
};
