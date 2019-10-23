/*
 * TIMER.h
 *
 *  Created on: Oct 14, 2019
 *      Author: Randa
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TIMER_config.h"

#define F_CPU 1000000UL
#define TIMER0_NUM_OF_OVERFLOW 2000
#define TIMER2_NUM_OF_OVERFLOW 4
extern volatile uint8 g_TIMER_flag;

typedef enum {NOK, OK} Func_status;
typedef void(*ptrTIMERFunctionCallback)(void);

Func_status TIMER_init(uint8 TimerID);
Func_status TIMER_start(uint8 timerID);
Func_status TIMER_stop(uint8 timerID);

void TIMER_sysTick_setCallBack(ptrTIMERFunctionCallback OS_sysTickFunction);


#endif /* TIMER_H_ */
