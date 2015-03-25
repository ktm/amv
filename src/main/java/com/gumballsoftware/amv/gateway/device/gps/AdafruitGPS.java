package com.gumballsoftware.amv.gateway.device.gps;

import com.gumballsoftware.amv.gateway.device.SerialPortManager;
import com.gumballsoftware.amv.model.GPS;
import com.gumballsoftware.amv.model.GlobalContext;
import jssc.SerialPort;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;
import net.sf.marineapi.nmea.parser.SentenceFactory;
import net.sf.marineapi.nmea.sentence.GGASentence;
import net.sf.marineapi.nmea.sentence.RMCSentence;
import net.sf.marineapi.nmea.sentence.Sentence;
import net.sf.marineapi.nmea.util.GpsFixQuality;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.Date;

@Component
public class AdafruitGPS implements SerialPortEventListener {

    private static final Logger logger = LoggerFactory.getLogger(AdafruitGPS.class);

    private static final String PMTK_SET_NMEA_UPDATE_100_MILLIHERTZ = "$PMTK220,10000*2F"; // Once every 10 seconds, 100 millihertz.
    private static final String PMTK_SET_NMEA_UPDATE_200_MILLIHERTZ = "$PMTK220,5000*1B";  // Once every 5 seconds, 200 millihertz.
    private static final String PMTK_SET_NMEA_UPDATE_1HZ = "$PMTK220,1000*1F";
    private static final String PMTK_SET_NMEA_UPDATE_5HZ = "$PMTK220,200*2C";
    private static final String PMTK_SET_NMEA_UPDATE_10HZ = "$PMTK220,100*2F";

    // Position fix update rate commands.
    private static final String PMTK_API_SET_FIX_CTL_100_MILLIHERTZ = "$PMTK300,10000,0,0,0,0*2C"; // Once every 10 seconds, 100 millihertz.
    private static final String PMTK_API_SET_FIX_CTL_200_MILLIHERTZ = "$PMTK300,5000,0,0,0,0*18";  // Once every 5 seconds, 200 millihertz.
    private static final String PMTK_API_SET_FIX_CTL_1HZ = "$PMTK300,1000,0,0,0,0*1C";
    private static final String PMTK_API_SET_FIX_CTL_5HZ = "$PMTK300,200,0,0,0,0*2F";

    // turn on only the second sentence (GPRMC)
    private static final String PMTK_SET_NMEA_OUTPUT_RMCONLY = "$PMTK314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29";
    // turn on GPRMC and GGA
    private static final String PMTK_SET_NMEA_OUTPUT_RMCGGA = "$PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28";
    // turn on ALL THE DATA
    private static final String PMTK_SET_NMEA_OUTPUT_ALLDATA = "$PMTK314,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0*28";
    // turn off output
    private static final String PMTK_SET_NMEA_OUTPUT_OFF = "$PMTK314,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*28";

    @Autowired
    private SerialPortManager serialPortManager;

    @Autowired
    private GlobalContext globalContext;

    private static final String deviceHandle = "GPS";
    private String deviceName;
    private StringBuilder sentenceStringBuilder = null;

    private GPS currentGPS;

    public void initialize(String deviceName) {
        logger.trace("initializing with device: " + deviceName);
        this.deviceName = deviceName;
        connect();
    }

    protected void connect() {
        try {
            serialPortManager.connectToDevice(deviceHandle, deviceName);
            serialPortManager.addSerialPortEventListener(deviceHandle, this, SerialPort.MASK_RXCHAR + SerialPort.MASK_CTS + SerialPort.MASK_DSR);

            logger.trace("sending output command");
            serialPortManager.writeToUart(deviceHandle, PMTK_SET_NMEA_OUTPUT_RMCGGA);

            logger.trace("sending update rate command");
            serialPortManager.writeToUart(deviceHandle, PMTK_SET_NMEA_UPDATE_10HZ);

            logger.trace("sending fix rate command");
            serialPortManager.writeToUart(deviceHandle, PMTK_API_SET_FIX_CTL_5HZ);
        } catch (Throwable th) {
            throw new RuntimeException("Unable to initialize GPS", th);
        }
    }

    protected void sentenceRead(String line) {
        try {
            Sentence newSentence = SentenceFactory.getInstance().createParser(line);
            handleSentence(newSentence);
        } catch (Throwable th) {
            throw new RuntimeException("sentenceRead failed: " + th, th);
        }
    }

    protected void handleSentence(Sentence s) {
        if (s == null) {
            return;
        }
        if (s.isValid() == false) {
            return;
        }
        if (s.isProprietary()) {
            return;
        }
        if (s instanceof RMCSentence) {
            handleRMC((RMCSentence)s);
        } else if (s instanceof GGASentence) {
            handleGGA((GGASentence)s);
        }
    }

    protected void handleRMC(RMCSentence sentence) {
        System.err.println("XXXXXXXXXX RWC sentence " + new Date());
        if (sentence.getStatus().toChar() == 'A') {
            return;
        }
        GPS newGPS = new GPS();

        newGPS.setLatitude(sentence.getPosition().getLatitude());
        newGPS.setLongitude(sentence.getPosition().getLongitude());
        newGPS.setLatitudeDirection(sentence.getPosition().getLatitudeHemisphere().toChar());
        newGPS.setLongitudeDirection(sentence.getPosition().getLongitudeHemisphere().toChar());
        newGPS.setTime(sentence.getTime().getMilliseconds());
        newGPS.setSpeed(sentence.getSpeed());

        currentGPS = newGPS;
        globalContext.setVar("gps", currentGPS);
    }

    protected void handleGGA(GGASentence sentence) {
        System.err.println("XXXXXXXXXX GGA sentence " + new Date());

        if (GpsFixQuality.INVALID.equals(sentence.getFixQuality())) {
            return;
        }
        GPS newGPS = new GPS();

        newGPS.setLatitude(sentence.getPosition().getLatitude());
        newGPS.setLongitude(sentence.getPosition().getLongitude());
        newGPS.setLatitudeDirection(sentence.getPosition().getLatitudeHemisphere().toChar());
        newGPS.setLongitudeDirection(sentence.getPosition().getLongitudeHemisphere().toChar());
        newGPS.setTime(sentence.getTime().getMilliseconds());
        // GGA does not include speed.
        if (currentGPS != null) {
            newGPS.setSpeed(currentGPS.getSpeed());
        }

        currentGPS = newGPS;
        globalContext.setVar("gps", currentGPS);
    }

    public void serialEvent(SerialPortEvent event) {
        if(event.isRXCHAR()){//If data is available
            if(event.getEventValue() == 10){
                try {
                    byte buffer[] = serialPortManager.readBytes(deviceHandle);
                    for (byte b : buffer) {
                        char c = (char)b;

                        if ( (c == '\n') || (c == '\r') ) {
                            continue;
                        }

                        if (c == '$') {                                          // begin new sentence
                            if (sentenceStringBuilder != null) {
                                sentenceRead(sentenceStringBuilder.toString());  // but finish old sentence first
                            }
                            sentenceStringBuilder = new StringBuilder();
                        }

                        if (sentenceStringBuilder == null)
                            continue;

                        sentenceStringBuilder.append(c);
                    }
                }
                catch (SerialPortException ex) {
                    logger.error("Serial port fail in AdafruitGPS serialEvent listener.", ex);
                }
            }
        }
        else if(event.isCTS()){//If CTS line has changed state
            if(event.getEventValue() == 1){//If line is ON
                logger.trace("CTS - ON");
            }
            else {
                logger.trace("CTS - OFF");
            }
        }
        else if(event.isDSR()){///If DSR line has changed state
            if(event.getEventValue() == 1){//If line is ON
                logger.trace("DSR - ON");
            }
            else {
                logger.trace("DSR - OFF");
            }
        }
    }
}
