/*
 * Timer_config.h
 *
 *  Created on: Sep 21, 2019
 *      Author: Randa
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

#include "std_types.h"

typedef enum {TIMER_0, TIMER_1, TIMER_2, num_of_timers} TIMER_t;

typedef enum {No_Clk,No_Prescaler,Prescaler_8,Prescaler_32 ,Prescaler_64,Prescaler_128,Prescaler_256,Prescaler_1024} Clk;

#define OVERFLOW 0	//Overflow Mode
#define OUTCOMP 1	//Output compare mode
#define PWM 2		//Pulse width modulation mode

#define INTERRUPT_ON 1		//Enable Timer Interrupt

#define IN_CLK 0	//Use internal clk
#define EX_CLK 1	//Use external clk

#define RTC 1		//Real Time clock enabled
#define ICU 1		//Input capture enabled

#define Wave_generation 1
#define Normal_Compare_match 0

#define OVERFLOW_OF_TIMER0 255
#define OVERFLOW_OF_TIMER1 65535
#define OVERFLOW_OF_TIMER2 255

#define WG_TOGGLE_Pin 0
#define WG_CLEAR_Pin 1
#define WG_SET_Pin 2

#define WG_Timer0_PIN PB3
#define WG_Timer1_ch_A_PIN PD5
#define WG_Timer1_ch_B_PIN PD4
#define WG_Timer1_ICP1_PIN PD6
#define WG_Timer2_PIN PD7


#define FAST_PWM 0
#define Phase_correct_PWM 1

#define INVERTING 0
#define NON_INVERTING 1

#define Falling_edge 0
#define Rising_edge 1

#define Positive_edge 0
#define Negative_edge 1

#define CHANNEL_A 0
#define CHANNEL_B 1

#define INITIALISED 1
#define UNINITIALISED 0

#define NA 0xff

typedef struct
{
	uint8 timer;
	uint8 mode;
	uint8 interrupt_flag;
	uint8 prescalar;
	uint8 clk_Oscillator;
	uint8 EX_clk_edge;
	uint16 Timer_initial;		//Timer register initial value
	uint16 Compare_reg;		//value to put inside the output compare register
	uint8 Timer1_channel;
	uint8 WG_PIN;
	uint8 inverting_mode;	//inverting or non-inverting mode
	uint8 OCR1A_PIN;
	uint8 OCR1B_PIN;
	uint8 is_configured;
}TIMER_cnfg_t;

extern TIMER_cnfg_t timersCfg[num_of_timers];

#endif /* TIMER_CONFIG_H_ */
