#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <string>
#include <iostream>

#include "serial.h"

int serial_init(std::string port_name)
{
    int fs_handle = open(port_name.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (fs_handle == -1)
    {
        //TODO error handling...
    }
    return fs_handle;
}

int serial_config(int fs_handle)
{
    struct termios options;
    tcgetattr(fs_handle, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(fs_handle, TCIFLUSH);
    tcsetattr(fs_handle, TCSANOW, &options);
    return fs_handle;
}

int serial_println(int fs_handle, std::string line, int len)
{
    int count = 0;
    if (fs_handle != -1) {
        char *cpstr = (char *)malloc((len+1) * sizeof(char));
        strcpy(cpstr, line.c_str());
        cpstr[len-1] = '\r';
        cpstr[len] = '\n';

        count = write(fs_handle, cpstr, len+1);
        if (count < 0) {
            std::cout << "serial_println fail: " << count  << std::endl;
        }
        free(cpstr);
    }

    return count;
}

// Read a line from UART.
// Return a 0 len string in case of problems with UART
int serial_readln(int fs_handle, std::string buffer, int len)
{
    char c;
    char *b = (char *)malloc((len+1) * sizeof(char));

    int rx_length = -1;
    while(1) {
        rx_length = read(fs_handle, (void*)(&c), 1);

        if (rx_length <= 0) {
            //wait for messages
            sleep(1);
        } else {
            if (c == '\n') {
                *b++ = '\0';
                break;
            }
            *b++ = c;
        }
    }
    buffer.assign(b, rx_length+1);
    return rx_length;
}

int serial_close(int fs_handle)
{
    close(fs_handle);
    return fs_handle;
}

