/*
 * OS.c
 *
 *  Created on: Oct 22, 2019
 *      Author: Randa
 */

#include "OS.h"

static Task_create_t Tasks_Buffer[Priority_level][Tasks_number];

static uint8 g_PriorityTasksNumber[Priority_level];


static volatile uint8 sysTick_flag = 0;
static volatile uint8 sysTick_counter = 0;

EnmOSError_t OS_Init (const OS_ConfigType* ConfigPtr )
{
	EnmOSError_t Error_status = fail;
	CPU_Sleep_init();
	if(ConfigPtr->sys_tick == Sys_tick)
	{
		Error_status = TIMER_init(OS_timer);
		TIMER_sysTick_setCallBack(OS_sysTick_callBack);
	}
	return Error_status;
}

EnmOSError_t OS_Create_Task(Task_create_t* Task_config)
{
	EnmOSError_t Error_status;
	uint8 Tasks_PriorityNumber;

	if(Task_config != NULL)
	{
		if((g_PriorityTasksNumber[Task_config->Priority] < Tasks_number) && (Task_config->Priority < Priority_level))
		{
			Task_config->Task_state = INIT;
			Tasks_PriorityNumber = g_PriorityTasksNumber[Task_config->Priority];
			Tasks_Buffer[Task_config->Priority][ Tasks_PriorityNumber] = *Task_config;
			g_PriorityTasksNumber[Task_config->Priority]++;
			Error_status = success;
		}
		else
		{
			Error_status = fail;
		}
	}
	else
	{
		Error_status = fail;
	}
	return Error_status;
}


void OS_Run(void)
{
	uint8 loop1_index;
	uint8 loop2_index;

	uint8 Task_state;

	TIMER_start(OS_timer);

	while(1)
	{
		if(sysTick_flag ==1)
		{
			for(loop1_index=0;loop1_index<Priority_level;loop1_index++)
			{
				for(loop2_index=0;loop2_index < g_PriorityTasksNumber[loop1_index];loop2_index++)
				{
					Task_state = Tasks_Buffer[loop1_index][loop2_index].Task_state;

					switch(Task_state)
					{
					case INIT:
					{
						if(Tasks_Buffer[loop1_index][loop2_index].periodicity == (sysTick_counter + 1))
						{
							Tasks_Buffer[loop1_index][loop2_index].Task_state = READY;
						}
					}
					break;
					case READY:
					{
						if(Tasks_Buffer[loop1_index][loop2_index].taskPtr != NULL)
						{
							(Tasks_Buffer[loop1_index][loop2_index].taskPtr)();

							if(Tasks_Buffer[loop1_index][loop2_index].periodicity != 1)
							{
								Tasks_Buffer[loop1_index][loop2_index].Task_state = WAITING;
								Tasks_Buffer[loop1_index][loop2_index].TimeOut = Tasks_Buffer[loop1_index][loop2_index].periodicity;
							}
						}
					}
					break;
					case WAITING:
					{
						if(Tasks_Buffer[loop1_index][loop2_index].TimeOut > 1)
						{
							Tasks_Buffer[loop1_index][loop2_index].TimeOut--;
						}
						else
						{
							Tasks_Buffer[loop1_index][loop2_index].Task_state = READY;
						}
					}
					break;
					}

					sysTick_flag = 0;
				}
			}
		}
	CPU_Sleep();
	}
}

void CPU_Sleep_init(void)
{
	MCUCR = 0;
}

void CPU_Sleep(void)
{
	MCUCR |= (1u << SE);
}

void OS_sysTick_callBack(void)
{
	MCUCR &= ~(1u << SE);
	sysTick_flag = 1;
	sysTick_counter++;
	PORTA ^= (1u << PA4);
}

EnmOSError_t OS_Delete_Task(Task_create_t* Delete_Task)
{
	EnmOSError_t Error_status = fail;
	uint8 index = Delete_Task->Priority;
	uint8 loop_index;
	if(Delete_Task->taskPtr != NULL)
	{
		for(loop_index = 0; loop_index < g_PriorityTasksNumber[index]; loop_index++)
		{
			if(Tasks_Buffer[index][loop_index].taskPtr == Delete_Task->taskPtr)
			{
				Tasks_Buffer[index][loop_index].Priority = NA;
				Tasks_Buffer[index][loop_index].taskPtr = NULL;
				Tasks_Buffer[index][loop_index].Task_state = DELETE;
			}
		}
		Error_status = success;
	}
	return Error_status;
}


void OS_DeInit (void)
{
	TIMER_stop(OS_timer);
}
