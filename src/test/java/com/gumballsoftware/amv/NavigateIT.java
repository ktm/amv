package com.gumballsoftware.amv;

import com.gumballsoftware.amv.model.GlobalContext;
import org.activiti.engine.RuntimeService;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

/**
 * Created by ktm on 3/23/15.
 */
public class NavigateIT {
    private AnnotationConfigApplicationContext context;

    @Test
    public void startDevices() {
        context = new AnnotationConfigApplicationContext();
        context.register(Application.class);
        context.refresh();

        RuntimeService runtimeService = context.getBean(RuntimeService.class);
        runtimeService.signalEventReceived("missionStart");

        GlobalContext globalContext = context.getBean(GlobalContext.class);

        // rightmost
        globalContext.setVar("navCourse", (byte)0xFF,  (byte)0x00, (byte)0x00);
        runtimeService.signalEventReceived("setSteering");

        try {
            Thread.sleep(2000);
        } catch (Throwable ignore){}

        // leftmost
        globalContext.setVar("navCourse", (byte)0xFF,  (byte)0x00, (byte)0xFE);
        runtimeService.signalEventReceived("setSteering");

        try {
            Thread.sleep(2000);
        } catch (Throwable ignore){}

        // center
        globalContext.setVar("navCourse", (byte)0xFF,  (byte)0x00, (byte) 0x7F);
        runtimeService.signalEventReceived("setSteering");
    }
}
