package com.gumballsoftware.amv.gateway.device;

import jssc.SerialPort;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;
import org.springframework.stereotype.Component;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by ktm on 1/17/15.
 */
@Component
public class SerialPortManager {
    Map<String, SerialPort> uartMap = new HashMap<>();

    public String connectToDevice(String handle, String devName) throws SerialPortException {
        SerialPort serialPort = new SerialPort(devName);
        serialPort.openPort();//Open serial port
        serialPort.setParams(SerialPort.BAUDRATE_9600,
                SerialPort.DATABITS_8,
                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);

        uartMap.put(handle, serialPort);

        byte command = (byte)0xFF;
        byte channel = (byte)0x00;
        byte center = 0x7F;
        byte leftMost = 0x00;
        int rightMost = 0xFE;

        byte[] bytes = new byte[]{command,  channel, leftMost};
        serialPort.writeBytes(bytes);

        try {Thread.sleep(2000);}catch (Throwable ignore) {}

        bytes[2] = (byte)rightMost;
        serialPort.writeBytes(bytes);

        return handle;
    }

    public int writeToUart(String handle, String value) throws SerialPortException {
        return writeToUart(handle, value.getBytes());
    }

    public int writeToUart(String handle, byte[] data) throws SerialPortException {
        SerialPort uart = uartMap.get(handle);
        ByteBuffer out = ByteBuffer.wrap(data);
        if (uart.writeBytes(data)) {
            return data.length;
        }
        return 0;
    }

    public byte[] readBytes(String handle, int buffSize) throws SerialPortException {
        SerialPort uart = uartMap.get(handle);
        return uart.readBytes();
    }

    public String readFromUart(String handle) throws SerialPortException {
        SerialPort uart = uartMap.get(handle);
        return uart.readString();
    }

    public void addSerialPortEventListener(String handle, SerialPortEventListener listener, int mask) throws SerialPortException {
        SerialPort uart = uartMap.get(handle);
        uart.addEventListener(listener, mask);
    }
}
