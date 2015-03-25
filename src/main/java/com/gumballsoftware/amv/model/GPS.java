package com.gumballsoftware.amv.model;

import javax.xml.stream.*;
import java.io.Serializable;

/**
 * Created by ktm on 2/3/15.
 */
public class GPS implements Serializable, Location {
    private double speed;
    private double latitude;
    private double longitude;
    private Compass latitudeDirection;
    private Compass longitudeDirection;
    private long time;

    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }

    public Compass getLongitudeDirection() {
        return longitudeDirection;
    }

    public void setLongitudeDirection(char longitudeDirection) {
        this.longitudeDirection = Compass.fromChar(longitudeDirection);
    }

    public Compass getLatitudeDirection() {
        return latitudeDirection;
    }

    public void setLatitudeDirection(char latitudeDirection) {
        this.latitudeDirection = Compass.fromChar(latitudeDirection);
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public void setSpeed(double arg) {
        speed = arg;
    }

    public double getSpeed() {
        return speed;
    }
}
