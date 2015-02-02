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
public class StartDevicesTest
{
    @Rule
    public ActivitiRule activitiRule = new ActivitiRule("activiti.cfg-mem-fullhistory.xml");

    @Test
    @Deployment(resources={"bpmn/startDevices.bpmn"})
    public void startDevices() {
        ProcessInstance pi = activitiRule.getRuntimeService().startProcessInstanceByKey("startdevices");
        List<HistoricDetail> historyVariables = activitiRule.getHistoryService()
                .createHistoricDetailQuery()
                .variableUpdates()
                .orderByVariableName()
                .asc()
                .list();
        assertNotNull(historyVariables);
    }
}
