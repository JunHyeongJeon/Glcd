/*
 * common.c
 *
 *  Created on: Apr 8, 2015
 *      Author: see
 */

// for delay loop sec count

#include "common.h"
#include "UART_drv_api.h"

unsigned long loops_per_sec = 16 * 1000 * 1000; // 16Mhz
__inline__ void __log(char * msg);

void writePin(pinNum pin, bool value) {
	// SIU.PCR[pin].R = PCR_OUTPUT;
	if(value < 1) value = 0;
	else value = 1;
	
	GPIO_SetState(pin, value);
	ndelay(100);
}

bool readPin(pinNum pin) {
	//SIU.PCR[pin].R = PCR_INPUT;
	return GPIO_GetState(pin);
}

__inline__ void __delay(unsigned int loops)
{
	if (loops != 0)
		__asm__ __volatile__("mtctr %0; 1: bdnz 1b" : :
                                       "r" (loops) : "ctr");
}

void sdelay(unsigned long secs){
	int i;
	for (i=0; i<secs*10; i++){
		mdelay(100);
	}
}

void mdelay(unsigned long msecs)
{
	unsigned long loops;

	/* compute (usecs * 2^32 / 10^3) * loops_per_sec / 2^32 */
	msecs *= 0x418570;                /* 2^32 / 10^3 */
	
	__asm__("mulhwu %0,%1,%2" : "=r" (loops) :
			"r" (msecs), "r" (loops_per_sec));
 	__delay(loops);
}

void ndelay(unsigned long nsecs) {
	unsigned long loops;

	/* compute (usecs * 2^32 / 10^9) * loops_per_sec / 2^32 */
	nsecs *= 0x0004;                /* 2^32 / 10^9 */
	
	__asm__("mulhwu %0,%1,%2" : "=r" (loops) :
			"r" (nsecs), "r" (loops_per_sec));
	
 	__delay(loops);
}

void udelay(unsigned long usecs)
{
	unsigned long loops;

	/* compute (usecs * 2^32 / 10^9) * loops_per_sec / 2^32 */
	usecs *= 0x10c6;                /* 2^32 / 10^9 */
	
	__asm__("mulhwu %0,%1,%2" : "=r" (loops) :
			"r" (usecs), "r" (loops_per_sec));
 	__delay(loops);
 }

__inline__ void __log(char * msg) {
	println(msg);
}

void print(char * msg) {
	unsigned long str_ln = 0;
	char ch = msg[str_ln];
	
	while(ch) {
		str_ln++;
		ch = msg[str_ln];
	}
	
	UartTxMsg((unsigned char *) msg, str_ln);
}
void println(char * msg) {
	print(msg);
	UartTxMsg((unsigned char *) "\r\n", 2);
}

void sys_log(char * msg) {
	__log(msg);
}
void err_log(char * msg) {
	__log(msg);
}
void dbg_log(char * msg) {
#ifdef DEBUG
	__log(msg);
#endif
}

long pow(long v, int n) {
  
  int i = 1;
  int ret = 1;
  
  if(n == 0) return 0;
  
  for(; i < n; i++) {
    ret *= v;
  }
  
  return ret;
}

int get_number_string_length(unsigned long val) {
	return get_number_length(val) + 1;
}

int get_number_length(unsigned long val) {
  int i = MAX_STOI_LENGTH;
  int cnt = 0;
  
  for(; i > 0; i--) {
    if((unsigned char) (val / pow(10, i)) != 0) {
      return i;
    }
    val = val % pow(10, i);
  }
  
  return 0;
}

void i_to_s(unsigned long val, char * ret) {
	int num_length = sizeof ret - 1;
  int i = num_length;
  
  for(; i > 0; i--) {
    ret[num_length - i] = (unsigned char) (val / pow(10, i)) + '0';
    val = val % pow(10, i);
  }
  
  ret[num_length] = '\0';
}


void Uart_100(int flag) {
	unsigned char cDigit[3];
	cDigit[0] = (unsigned char) (flag / 100) + '0';
	flag = flag % 100;
	cDigit[1] = (unsigned char) (flag / 10) + '0';
	flag = flag % 10;
	cDigit[2] = (unsigned char) flag + '0';
	UartTxMsg(cDigit, 3);
}

void Uart_1000(int flag) {
	unsigned char cDigit[4];
	cDigit[0] = (unsigned char) (flag / 1000) + '0';
	flag = flag % 1000;
	cDigit[1] = (unsigned char) (flag / 100) + '0';
	flag = flag % 100;
	cDigit[2] = (unsigned char) (flag / 10) + '0';
	flag = flag % 10;
	cDigit[3] = (unsigned char) flag + '0';
	UartTxMsg(cDigit, 4);
}

void Uart_10000(int flag) {
	unsigned char cDigit[5];
	cDigit[0] = (unsigned char) (flag / 10000) + '0';
	flag = flag % 10000;
	cDigit[1] = (unsigned char) (flag / 1000) + '0';
	flag = flag % 1000;
	cDigit[2] = (unsigned char) (flag / 100) + '0';
	flag = flag % 100;
	cDigit[3] = (unsigned char) (flag / 10) + '0';
	flag = flag % 10;
	cDigit[4] = (unsigned char) flag + '0';
	UartTxMsg(cDigit, 5);
}

