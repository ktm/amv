package com.gumballsoftware.amv.service;

import com.gumballsoftware.amv.gateway.device.gps.AdafruitGPS;
import com.gumballsoftware.amv.model.GlobalContext;
import com.gumballsoftware.amv.model.Location;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import static java.lang.Math.cos;
import static java.lang.Math.sqrt;

/**
 * Created by ktm on 3/3/15.
 */
@Component
public class Navigation {

    static final double EarthRadius = 6371000; //  meters

    @Autowired
    GlobalContext globalContext;

    public boolean areLocationsEquivalent(Location lhs, Location rhs) {
        return areLocationsEquivalent(lhs, rhs, 10);
    }

    // tolerance is in meters; if tolerance is 5 and d < 5 then the 2 locations are no more than 5 meters apart
    public boolean areLocationsEquivalent(Location lhs, Location rhs, double tolerance) {
        boolean retval = false;
        if ( (lhs == null) || (rhs == null)) {
            return retval;
        }
        double d = distance(lhs.getLongitude(), rhs.getLongitude(), lhs.getLatitude(), rhs.getLongitude());
        retval = d <= tolerance;

        return retval;
    }

    public double distance(double lonp, double lon1, double latp, double lat1) {
/*
        Equirectangular approximation
        http://gis.stackexchange.com/a/21100
*/
        double p1 = (lonp - lon1) * cos(0.5 * (latp + lat1)); //convert lat/lon to radians
        double p2 = (latp - lat1);

        double distance = EarthRadius * sqrt( p1*p1 + p2*p2); // in meters
        return distance;
    }
}
