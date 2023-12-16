/*
 * scheduler.c
 *
 *  Created on: Nov 8, 2023
 *      Author: Admin
 */

#include "main.h"
#include "scheduler.h"
#include "mode_processing.h"

#define TIME_CYCLE 10
static uint32_t newTaskID = 0;

void SCH_Init(void) {
	unsigned char i ;
	for(i = 0; i < SCH_MAX_TASKS; i++) {
		SCH_Delete_Task(i);
	}
	// Reset the global error variable
	// − SCH_Delete_Task ( ) will generate an e r ro r code ,
	// ( because the task array i s empty)
	// Error_code_G = 0;
	// Timer_init();
	// Watchdog_init ( ) ;
}

static uint32_t Get_New_Task_ID(void){
	newTaskID++;
	if(newTaskID == NO_TASK_ID){
		newTaskID++;
	}
	return newTaskID;
}

uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
	uint8_t newTaskIndex = 0;
	uint32_t sumDelay = 0;
	uint32_t newDelay = 0;

	for(newTaskIndex = 0; newTaskIndex < SCH_MAX_TASKS; newTaskIndex++){
		sumDelay = sumDelay + SCH_tasks_G[newTaskIndex].Delay;
		if(sumDelay > DELAY){
			newDelay = DELAY - (sumDelay - SCH_tasks_G[newTaskIndex].Delay);
			SCH_tasks_G[newTaskIndex].Delay = sumDelay - DELAY;
			for(uint8_t i = SCH_MAX_TASKS - 1; i > newTaskIndex; i--){
//				if(SCH_tasks_G[i - 1].pTask != 0)
				{
					SCH_tasks_G[i].pTask = SCH_tasks_G[i - 1].pTask;
					SCH_tasks_G[i].Period = SCH_tasks_G[i - 1].Period;
					SCH_tasks_G[i].Delay = SCH_tasks_G[i - 1].Delay;
//					SCH_tasks_G[i].RunMe = SCH_tasks_G[i - 1].RunMe;
					SCH_tasks_G[i].TaskID = SCH_tasks_G[i - 1].TaskID;
				}
			}
			SCH_tasks_G[newTaskIndex].pTask = pFunction;
			SCH_tasks_G[newTaskIndex].Delay = newDelay;
			SCH_tasks_G[newTaskIndex].Period = PERIOD;
			if(SCH_tasks_G[newTaskIndex].Delay == 0){
				SCH_tasks_G[newTaskIndex].RunMe = 1;
			} else {
				SCH_tasks_G[newTaskIndex].RunMe = 0;
			}
			SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();
			return SCH_tasks_G[newTaskIndex].TaskID;
		} else {
			if(SCH_tasks_G[newTaskIndex].pTask == 0x0000){
				SCH_tasks_G[newTaskIndex].pTask = pFunction;
				SCH_tasks_G[newTaskIndex].Delay = DELAY - sumDelay;
				SCH_tasks_G[newTaskIndex].Period = PERIOD;
				if(SCH_tasks_G[newTaskIndex].Delay == 0){
					SCH_tasks_G[newTaskIndex].RunMe = 1;
				} else {
					SCH_tasks_G[newTaskIndex].RunMe = 0;
				}
				SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();
				return SCH_tasks_G[newTaskIndex].TaskID;
			}
		}
	}
	return SCH_tasks_G[newTaskIndex].TaskID;
}
void SCH_Dispatch_Tasks(void){
	if(SCH_tasks_G[0].RunMe > 0) {
		(*SCH_tasks_G[0].pTask)(); // Run the task
		SCH_tasks_G[0].RunMe = 0; // Reset / reduce RunMe flag
		sTask temtask = SCH_tasks_G[0];
		SCH_Delete_Task(temtask.TaskID);
		if (temtask.Period != 0) {
			SCH_Add_Task(temtask.pTask, temtask.Period, temtask.Period);
		}
	}
}

uint8_t SCH_Delete_Task(uint32_t taskID){
	uint8_t Return_code  = 0;
	uint8_t taskIndex;
	uint8_t j;
	if(taskID != NO_TASK_ID){
		for(taskIndex = 0; taskIndex < SCH_MAX_TASKS; taskIndex ++){
			if(SCH_tasks_G[taskIndex].TaskID == taskID){
				Return_code = 1;
				if(taskIndex != 0 && taskIndex < SCH_MAX_TASKS - 1){
					if(SCH_tasks_G[taskIndex+1].pTask != 0x0000){
						SCH_tasks_G[taskIndex+1].Delay += SCH_tasks_G[taskIndex].Delay;
					}
				}

				for( j = taskIndex; j < SCH_MAX_TASKS - 1; j ++){
					SCH_tasks_G[j].pTask = SCH_tasks_G[j+1].pTask;
					SCH_tasks_G[j].Period = SCH_tasks_G[j+1].Period;
					SCH_tasks_G[j].Delay = SCH_tasks_G[j+1].Delay;
					SCH_tasks_G[j].RunMe = SCH_tasks_G[j+1].RunMe;
					SCH_tasks_G[j].TaskID = SCH_tasks_G[j+1].TaskID;
				}
				SCH_tasks_G[j].pTask = 0;
				SCH_tasks_G[j].Period = 0;
				SCH_tasks_G[j].Delay = 0;
				SCH_tasks_G[j].RunMe = 0;
				SCH_tasks_G[j].TaskID = 0;
				return Return_code;
			}
		}
	}
	return Return_code; // return status
}

void SCH_Update(void){
	// Check if there is a task at this location
	if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
		if(SCH_tasks_G[0].Delay > 0){
			SCH_tasks_G[0].Delay = SCH_tasks_G[0].Delay - 1;
		}
		if (SCH_tasks_G[0].Delay == 0) {
			SCH_tasks_G[0].RunMe = 1;
		}
	}
}


