#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <string>
int serial_init(std::string);

void serial_config(int);

void serial_println(int, std::string, int);

void serial_readln(int, std::string, int);

void serial_close(int);
#endif
