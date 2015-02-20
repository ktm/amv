package com.gumballsoftware.amv.model;

import org.springframework.stereotype.Component;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by ktm on 2/18/15.
 */
@Component
public class GlobalContext {
    private Map<String, Serializable>varMap = new HashMap<>();

    public void setVar(String name, byte ... bytes) {
        varMap.put(name, bytes);
    }

    public void setVar(String name, Serializable value) {
        varMap.put(name, value);
    }

    public Serializable getVar(String name) {
        return varMap.get(name);
    }
}
