/*
 * main.c
 *
 *  Created on: Oct 23, 2019
 *      Author: Randa
 */

#include "OS.h"

void toggleLed1(void);
void toggleLed2(void);
void toggleLed3(void);
void toggleLed4(void);

OS_ConfigType OS_sysTick = { Sys_tick };

Task_create_t Task1 = {0, 3, toggleLed1, NA};
Task_create_t Task2 = {1, 1, toggleLed2, NA};
Task_create_t Task3 = {2, 1, toggleLed3, NA};
Task_create_t Task4 = {0, 2, toggleLed4, NA};


void toggleLed1(void)
{
	PORTA ^= (1u << PA0);
	OS_Delete_Task(&Task3);
}


void toggleLed2(void)
{
	PORTA ^= (1u << PA1);
}


void toggleLed3(void)
{
	PORTA ^= (1u << PA2);
}

void toggleLed4(void)
{
	PORTA ^= (1u << PA3);
}

int main(void)
{
	DDRA |= (1u << PA0);
	DDRA |= (1u << PA1);
	DDRA |= (1u << PA2);
	DDRA |= (1u << PA3);
	DDRA |= (1u << PA4);


	PORTA &=~(1u << PA0);
	PORTA |= (1u << PA1);
	PORTA &=~(1u << PA2);
	PORTA |= (1u << PA3);
	PORTA |= (1u << PA4);


	OS_Init (&OS_sysTick);

	OS_Create_Task(&Task1);
	OS_Create_Task(&Task2);
	OS_Create_Task(&Task3);
	OS_Create_Task(&Task4);


	OS_Run();

}
