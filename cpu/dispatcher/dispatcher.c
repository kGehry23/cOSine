/**
 ********************************************************************************
 * @file    dispatcher.c
 * 
 * @author  Kai Gehry
 * @date    2026-04-10
 *
 * @brief   Dispatcher function definitions.
 *     
 ********************************************************************************
 */

/************************************
* INCLUDES
************************************/
#include "dispatcher.h"


/************************************
* FUNCTION DEFINITIONS
************************************/

//Dispatches a new task provided by the scheduler
void dispatch(task* old_task, task* new_task)
{
    switch_state(&old_task->registers, &new_task->registers);
}
