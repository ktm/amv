package com.gumballsoftware.amv;

import org.activiti.engine.RepositoryService;
import org.activiti.engine.RuntimeService;
import org.activiti.engine.TaskService;
import org.activiti.engine.task.Task;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * Created by ktm on 1/15/15.
 */
@Component
public class ActivitiService {

    private RuntimeService runtimeService;

    private TaskService taskService;

    private RepositoryService repositoryService;

    @Autowired
    public ActivitiService(RuntimeService rs, TaskService ts, RepositoryService rps) {
        runtimeService = rs;
        taskService = ts;
        repositoryService = rps;
    }

    public void start() {
        startProcess("STEERING_PROCESS");
    }

    public void startProcess(String processKey) {
        runtimeService.startProcessInstanceByKey(processKey);
    }

    public List<Task> getTasks(String assignee) {
        return taskService.createTaskQuery().taskAssignee(assignee).list();
    }

    public void deployPlan(String process) {
        repositoryService.createDeployment().addClasspathResource("bpmn/"+process + ".bpmn").deploy();
    }

    public void createDemoUsers() {
    }
}
