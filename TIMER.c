/*
 * TIMER.c
 *
 *  Created on: Oct 14, 2019
 *      Author: Randa
 */
#include "TIMER.h"

//static volatile uint8 TIMER0_delay = 0;
//static volatile uint8 TIMER2_delay = 0;

static volatile void_func_ptr g_TIMER_ptr = NULL;
volatile uint8 g_TIMER_flag = 0;

//Clk set function
Func_status TIMER_start(uint8 TimerID)
{
	Func_status retval = OK;
	switch (TimerID)
	{
	case TIMER_0:
		if(timersCfg[TimerID].clk_Oscillator == IN_CLK)
		{
			switch (timersCfg[TimerID].prescalar)
			{
			case No_Prescaler:
				TCCR0 |= (1u << FOC0 )| (1u << CS00);
				break;
			case Prescaler_8:
				TCCR0 |= (1u << FOC0) |( 1u << CS01);
				break;
			case Prescaler_64:
				TCCR0 |= (1u << FOC0) | (1u << CS01) |( 1u << CS00);
				break;
			case Prescaler_256:
				TCCR0 |= (1u << FOC0) |( 1u << CS02);
				break;
			case Prescaler_1024:
				TCCR0 |= (1u << FOC0 )|( 1u << CS02 )|( 1u << CS00);
				break;
			default:
				retval=NOK;
			}
		}
		else if(timersCfg[TimerID].clk_Oscillator == EX_CLK)
		{
			if(timersCfg[TimerID].EX_clk_edge == Falling_edge)
			{
				TCCR0 = (1u << FOC0) |(1u << CS02) | (1u << CS01);
			}
			else if(timersCfg[TimerID].EX_clk_edge == Rising_edge)
			{
				TCCR0 = (1u << FOC0) | (1u << CS02) | (1u << CS01)|( 1u << CS00);
			}
			else
			{
				retval=NOK;
			}
		}
		else
		{
			retval=NOK;
		}
	break;
	case TIMER_1:
		if(timersCfg[TimerID].clk_Oscillator == IN_CLK)
		{
			switch (timersCfg[TimerID].prescalar)
			{
			case No_Prescaler:
				TCCR1B |= (1u << CS10);
				break;
			case Prescaler_8:
				TCCR1B |= ( 1u << CS11);
				break;
			case Prescaler_64:
				TCCR1B |= (1u << CS11) |( 1u << CS10);
				break;
			case Prescaler_256:
				TCCR1B |= (1u << CS12);
				break;
			case Prescaler_1024:
				TCCR1B |= (1u << CS12 )|( 1u << CS10);
				break;
			default:
				retval=NOK;
			}
		}
		else if(timersCfg[TimerID].clk_Oscillator == EX_CLK)
		{
			if(timersCfg[TimerID].EX_clk_edge == Falling_edge)
			{
				TCCR1B = (1u << CS12) | (1u << CS11);
			}
			else if(timersCfg[TimerID].EX_clk_edge == Rising_edge)
			{
				TCCR1B = (1u << CS12) | (1u << CS11)|( 1u << CS10);
			}
			else
			{
				retval=NOK;
			}
		}
		else
		{
			retval=NOK;
		}
	break;
	case TIMER_2:
		if(timersCfg[TimerID].clk_Oscillator == IN_CLK)
		{
			switch(timersCfg[TimerID].prescalar)
			{
			case No_Prescaler:
				TCCR2 |= (1u << FOC2) | (1u << CS20);
			break;
			case Prescaler_8:
				TCCR2 |= (1u << FOC2) | (1u << CS21);
			break;
			case Prescaler_32:
				TCCR2 |= (1u << FOC2) | (1u << CS21) | (1u << CS20);
			break;
			case Prescaler_64:
				TCCR2 |= (1u << FOC2) | (1u << CS22);
			break;
			case Prescaler_128:
				TCCR2 |= (1u << FOC2) | (1u << CS20) | (1u << CS22);
			break;
			case Prescaler_256:
				TCCR2 |= (1u << FOC2) | (1u << CS21) | (1u << CS22);
			break;
			case Prescaler_1024:
				TCCR2 |= (1u << FOC2) | (1u << CS20) | (1u << CS20) | (1u << CS22);
			break;
			default:
				retval = NOK;
			}
		}
		else
		{
			retval = NOK;
		}
	break;
	}
	return retval;
}

//Timer modes initialization function
Func_status TIMER_init(uint8 TimerID)
{

	Func_status status = OK;
	switch(TimerID)
	{
	case TIMER_0:
		TCNT0 = timersCfg[TIMER_0].Timer_initial;
		TCCR0 |= (1u << FOC0 );
		switch(timersCfg[TIMER_0].mode)
		{
		case OVERFLOW:
			if(timersCfg[TIMER_0].interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE0);
			}
			else if(timersCfg[TIMER_0].interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE0);
			}
		break;
		case OUTCOMP:
			TCCR0 = (1u << FOC0 | 1u << WGM01);
			OCR0 = (uint8)timersCfg[TIMER_0].Compare_reg;
			if(timersCfg[TIMER_0].interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << OCIE0);
			}
			else if(timersCfg[TIMER_0].interrupt_flag == NA)
			{
				TIMSK &= ~(1u << OCIE0);
			}
		break;
		default:
			status = NOK;
			timersCfg[TIMER_0].is_configured = UNINITIALISED;
		}
	break;
	case TIMER_1:
		TCNT1 = timersCfg[TIMER_1].Timer_initial;
		switch(timersCfg[TIMER_1].mode)
		{
		case OVERFLOW:
			TCCR1A = (1u << FOC1A) | (1u << FOC1B);
			if(timersCfg[TIMER_1].interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE1);
			}
			else if(timersCfg[TIMER_1].interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE1);
			}
		break;
		case OUTCOMP:
			TCCR1A = (1u << FOC1A) | (1u << FOC1B);
			if(timersCfg[TIMER_1].Timer1_channel == CHANNEL_A)
			{
				OCR1A = timersCfg[TIMER_1].Compare_reg;
				TCCR1B = (1 << WGM12);
				if(timersCfg[TIMER_1].interrupt_flag == INTERRUPT_ON)
				{
					SREG  |= (1u << 7);
					TIMSK |= (1u << OCIE1A);
				}
				else if(timersCfg[TIMER_1].interrupt_flag == NA)
				{
					TIMSK &= ~(1u << OCIE1A);
				}
			}
			else if(timersCfg[TIMER_1].Timer1_channel == CHANNEL_B)
			{
				OCR1B = timersCfg[TIMER_1].Compare_reg;
				if(timersCfg[TIMER_1].interrupt_flag == INTERRUPT_ON)
				{
					SREG  |= (1u << 7);
					TIMSK |= (1u << OCIE1B);
				}
				else if(timersCfg[TIMER_1].interrupt_flag == NA)
				{
					TIMSK &= ~(1u << OCIE1B);
				}
			}
			else
			{
				timersCfg[TIMER_1].is_configured = UNINITIALISED;
				status = NOK;
			}

		break;
		default:
			timersCfg[TIMER_1].is_configured = UNINITIALISED;
			status = NOK;
		}
	break;
	case TIMER_2:
		TCNT2 = timersCfg[TIMER_2].Timer_initial;
		TCCR2 |= (1u << FOC2);
		switch(timersCfg[TIMER_2].mode)
		{
		case OVERFLOW:
			if(timersCfg[TIMER_2].interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << TOIE2);
			}
			else if(timersCfg[TIMER_2].interrupt_flag == NA)
			{
				TIMSK &= ~(1u << TOIE2);
			}
		break;
		case OUTCOMP:
			TCCR2 = (1u << FOC2 | 1u << WGM21);
			OCR2 = (uint8)timersCfg[TIMER_2].Compare_reg;
			if(timersCfg[TIMER_2].interrupt_flag == INTERRUPT_ON)
			{
				SREG  |= (1 << 7);
				TIMSK |= (1u << OCIE2);
			}
			else if(timersCfg[TIMER_2].interrupt_flag == NA)
			{
				TIMSK &= ~(1u << OCIE2);
			}
		break;
		default:
			status = NOK;
			timersCfg[TIMER_2].is_configured = UNINITIALISED;
		}
	break;
	default:
		timersCfg[TIMER_2].is_configured = UNINITIALISED;
		status = NOK;
	}
	return status;
}

Func_status TIMER_stop(uint8 TimerID)
{
	Func_status status = OK;
	switch (TimerID)
	{
	case TIMER_0:
		TCCR0 &= ~((1u << CS02 ) | (1u << CS01) | (1u << CS00));
	break;
	case TIMER_1:
		TCCR1B &= ~((1u << CS12 ) | (1u << CS11) | (1u << CS10));
	break;
	case TIMER_2:
		TCCR2 &= ~((1u << CS22 ) | (1u << CS21) | (1u << CS20));
	break;
	default:
		status = NOK;
	}
	return status;
}


void TIMER_sysTick_setCallBack(ptrTIMERFunctionCallback OS_sysTickFunction)
{
	g_TIMER_ptr = OS_sysTickFunction;
}

ISR(TIMER2_COMP_vect)
{
	if(g_TIMER_ptr != NULL)
	{
		g_TIMER_ptr();
	}
}
