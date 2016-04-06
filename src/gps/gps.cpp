#include "gps.h"
#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include "nmea.h"
#include "../serial/serial.hxx"
#include "../model/context.hxx"

// Compute the GPS location using decimal scale
uint8_t process_gps_location(std::string gpsrecord, uint8_t status) {
    loc_t coord;

        gpgga_t gpgga;
        gprmc_t gprmc;

        switch (nmea_get_message_type(gpsrecord)) {
            case NMEA_GPGGA:
                nmea_parse_gpgga(gpsrecord, &gpgga);

                gps_convert_deg_to_dec(&(gpgga.latitude), gpgga.lat, &(gpgga.longitude), gpgga.lon);

                coord.latitude = gpgga.latitude;
                coord.longitude = gpgga.longitude;
                coord.altitude = gpgga.altitude;
                Context::Instance().write("gps_latitude", coord.latitude);
                Context::Instance().write("gps_longitude", coord.longitude);
                Context::Instance().write("gps_altitude", coord.altitude);
                status |= NMEA_GPGGA;
                break;
            case NMEA_GPRMC:
                nmea_parse_gprmc(gpsrecord, &gprmc);

                coord.speed = gprmc.speed;
                coord.course = gprmc.course;

                Context::Instance().write("gps_speed", coord.speed);
                Context::Instance().write("gps_course", coord.course);
                status |= NMEA_GPRMC;
                break;
        }

    return status;
}

// Convert lat e lon to decimals (from deg)
void gps_convert_deg_to_dec(double *latitude, char ns,  double *longitude, char we)
{
    double lat = (ns == 'N') ? *latitude : -1 * (*latitude);
    double lon = (we == 'E') ? *longitude : -1 * (*longitude);

    *latitude = gps_deg_dec(lat);
    *longitude = gps_deg_dec(lon);
}

double gps_deg_dec(double deg_point)
{
    double ddeg;
    double sec = modf(deg_point, &ddeg)*60;
    int deg = (int)(ddeg/100);
    int min = (int)(deg_point-(deg*100));

    double absdlat = round(deg * 1000000.);
    double absmlat = round(min * 1000000.);
    double absslat = round(sec * 1000000.);

    return round(absdlat + (absmlat/60) + (absslat/3600)) /1000000;
}
