/*
 * common.h
 *
 *  Created on: Apr 8, 2015
 *      Author: see
 */

#ifndef COMMON_H_
#define COMMON_H_

// general libraries

#include "gpio_drv.h"
#include "jdp.h"
#include "UART_drv_api.h"

#include "config.h"

#define DEBUG

// types
typedef unsigned char byte;
typedef unsigned short pinNum;
typedef unsigned char bool;
typedef char * string;

// general values

#define true 1
#define false 0

#define PCR_OUTPUT		0x0201
#define PCR_INPUT 		0x0101

#define _BV(bit) (1 << (bit))

#define MAX_STOI_LENGTH (sizeof(unsigned long) - 1)

// functions

void writePin(pinNum pin, bool value);
bool readPin(pinNum pin);

#define write_pin(X,Y) writePin(X, Y)
#define read_pin(X) read_pin(X)

void sdelay(unsigned long secs);
void mdelay(unsigned long msecs);
void udelay(unsigned long usecs); // micro seconds delay
void ndelay(unsigned long nsecs);

void print(char * msg);
void println(char * msg);

long pow(long v, int n);
int get_number_length(unsigned long val);
int get_number_string_length(unsigned long val);
void i_to_s(unsigned long val, string ret);

void sys_log(string msg);
void err_log(string msg);
void dbg_log(string msg);

// deprecated

void Uart_100(int flag);
void Uart_1000(int flag);
void Uart_10000(int flag);

#endif /* COMMON_H_ */
