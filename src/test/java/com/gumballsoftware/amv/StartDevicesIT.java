package com.gumballsoftware.amv;

import org.activiti.engine.HistoryService;
import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.history.HistoricDetail;
import org.activiti.engine.runtime.ProcessInstance;
import org.junit.Ignore;
import org.junit.Test;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

import java.util.List;

import static org.junit.Assert.assertNotNull;
@Ignore
public class StartDevicesIT {
    private AnnotationConfigApplicationContext context;

    @Test
    public void startDevices() {
        context = new AnnotationConfigApplicationContext();
        context.register(Application.class);
        context.refresh();

        RepositoryService repositoryService = context.getBean(RepositoryService.class);
        RuntimeService runtimeService = context.getBean(RuntimeService.class);
        ProcessInstance pi = runtimeService.startProcessInstanceByKey("startdevices");
        HistoryService hs = context.getBean(HistoryService.class);

        List<HistoricDetail> historyVariables = hs
                .createHistoricDetailQuery()
                .variableUpdates()
                .orderByVariableName()
                .asc()
                .list();

        assertNotNull(historyVariables);
    }
}
