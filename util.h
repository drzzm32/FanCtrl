#include "STC15.h"
#include <intrins.h>

#ifndef __UTIL_H_
#define __UTIL_H_

#define uint8_t unsigned char

#define FAN_A P10
#define FANS_A P11
#define FAN_B P12
#define FANS_B P13
#define FAN_C P14
#define FANS_C P15

#define FAN_V (~(P3 & 0x7) & 0x7)
#define FANC_A !P33
#define FANC_B !P36
#define FANC_C !P37

#define CNT_MAX 7
static uint8_t cntA, cntB, cntC;
static uint8_t posA, posB, posC;

void portInit() {
	P1M0 = 0x00;	P1M1 = 0x2A;
	P3M0 = 0x00;	P3M1 = 0x00;
}

void timerInit() {
	/*24MHz@10us*/
	AUXR |= 0x80;
	TMOD &= 0xF0;
	TL0 = 0x10;	
	TH0 = 0xFF;
	TF0 = 0;
	TR0 = 1;
	ET0 = 1;
	EA = 1;
}

void timerInterrupt() interrupt 1 using 1 {
	FAN_A = !(cntA < posA);
	cntA = (cntA < CNT_MAX ? cntA + 1 : 0);
	FAN_B = !(cntB < posB);
	cntB = (cntB < CNT_MAX ? cntB + 1 : 0);
	FAN_C = !(cntC < posC);
	cntC = (cntC < CNT_MAX ? cntC + 1 : 0);
}

void pwmInit() {
	portInit();
	FAN_A = 1; FAN_B = 1; FAN_C = 1;
	cntA = 0; cntB = 0; cntC = 0;
	posA = 0; posB = 0; posC = 0;
	timerInit();
}

#endif