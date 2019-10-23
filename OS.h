/*
 * OS.h
 *
 *  Created on: Oct 22, 2019
 *      Author: Randa
 */

#ifndef OS_H_
#define OS_H_


#include "std_types.h"
#include "micro_config.h"
#include "TIMER.h"


#define OS_timer TIMER_2
/*System tick every 1ms*/
#define Sys_tick 1U
#define Tasks_number 5
#define Priority_level 5

#define INIT 0
#define READY 1
#define WAITING 2
#define DELETE 3

typedef void(*ptrOSFunctionCallback)(void);

typedef struct {
	uint8 Priority;
	uint8 periodicity;
	ptrOSFunctionCallback taskPtr;
	uint8 Task_state;
	uint8 TimeOut;
}Task_create_t;

typedef struct {
	uint8 sys_tick;
} OS_ConfigType ;

typedef enum {fail,success}EnmOSError_t;

EnmOSError_t OS_Init (const OS_ConfigType * ConfigPtr );
void OS_DeInit (void);
void OS_Run(void);
EnmOSError_t OS_Create_Task(Task_create_t* Task_config);
EnmOSError_t OS_Delete_Task(Task_create_t* Delete_Task);
void OS_sysTick_callBack(void);
void CPU_Sleep_init(void);
void CPU_Sleep(void);
#endif /* OS_H_ */
