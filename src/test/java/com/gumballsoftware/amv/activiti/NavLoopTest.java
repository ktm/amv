package com.gumballsoftware.amv.activiti;

import org.activiti.engine.history.HistoricDetail;
import org.activiti.engine.runtime.ProcessInstance;
import org.activiti.engine.test.ActivitiRule;
import org.activiti.engine.test.Deployment;
import org.junit.Ignore;
import org.junit.Rule;
import org.junit.Test;

import java.util.List;

import static org.junit.Assert.assertNotNull;

@Ignore
public class NavLoopTest
{
    @Rule
    public ActivitiRule activitiRule = new ActivitiRule("activiti.cfg-mem-fullhistory.xml");

    @Test
    @Deployment(resources={"bpmn/navigateToWaypoint.bpmn"})
    public void startDevices() {
        ProcessInstance pi = activitiRule.getRuntimeService().startProcessInstanceByKey("navigateToWaypointProcess");

        assertNotNull(pi);
//        Thread.sleep(30000);
    }
}
