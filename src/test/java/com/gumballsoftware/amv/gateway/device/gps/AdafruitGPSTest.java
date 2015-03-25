package com.gumballsoftware.amv.gateway.device.gps;

import com.gumballsoftware.amv.Application;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

/**
 * Created by ktm on 3/2/15.
 */
public class AdafruitGPSTest {

    private AnnotationConfigApplicationContext context;

    @Test
    public void initGPS() {
        context = new AnnotationConfigApplicationContext();
        context.register(Application.class);
        context.refresh();

        AdafruitGPS gpsBean = context.getBean(AdafruitGPS.class);
        gpsBean.initialize("/dev/ttyUSB0");
try {
Thread.sleep(30000);
}catch(Throwable ignore){}
    }
}
