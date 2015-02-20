package com.gumballsoftware.amv;

import com.gumballsoftware.amv.model.GlobalContext;
import org.activiti.engine.HistoryService;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.history.HistoricDetail;
import org.activiti.engine.runtime.ProcessInstance;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.Assert.assertNotNull;

public class NavLoopIT {
    private AnnotationConfigApplicationContext context;

    @Test
    public void startDevices() {
        context = new AnnotationConfigApplicationContext();
        context.register(Application.class);
        context.refresh();

        RuntimeService runtimeService = context.getBean(RuntimeService.class);
        runtimeService.signalEventReceived("missionStart");

        GlobalContext globalContext = context.getBean(GlobalContext.class);

        // leftmost
        globalContext.setVar("navCourse", (byte)0xFF,  (byte)0x00, (byte)0x00);
        runtimeService.signalEventReceived("setSteering");

        try {
            Thread.sleep(2000);
        } catch (Throwable ignore){}

        // rightmost
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
