#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <string>
int serial_init(std::string);

int serial_config(int);

int serial_println(int, std::string, int);

int serial_readln(int, std::string& , int);

int serial_close(int);
#endif
