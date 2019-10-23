/*
 * Timer_config.c
 *
 *  Created on: Sep 25, 2019
 *      Author: Randa
 */

#include "TIMER_config.h"



TIMER_cnfg_t timersCfg[num_of_timers]=
{
		{TIMER_0, OUTCOMP, INTERRUPT_ON, Prescaler_8, IN_CLK, NA, 0x00, 125, NA, NA, NA, NA, NA, INITIALISED},
		{TIMER_1, OUTCOMP, INTERRUPT_ON, No_Prescaler, IN_CLK, NA, 0x00, 1000, CHANNEL_A, NA, NA, NA, NA, INITIALISED},
		{TIMER_2, OUTCOMP, INTERRUPT_ON, Prescaler_8, IN_CLK, NA, 0x00, 125, NA, NA, NA, NA, NA, INITIALISED},
};



