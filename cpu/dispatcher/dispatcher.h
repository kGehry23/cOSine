/**
 ********************************************************************************
 * @file    dispatcher.h
 * 
 * @author  Kai Gehry
 * @date    2026-04-10
 *
 * @brief   Dispatcher function prototypes and defines.
 *     
 ********************************************************************************
 */

#ifndef DISPATCHER_H 
#define DISPATCHER_H

/************************************
* INCLUDES
************************************/
#include "../../task/task.h"


/************************************
* FUNCTION PROTOTYPES
************************************/

/*!
 * @brief Dispatches a new task
 * @param old_task Task to save the context of
 * @param new_task Task to switch to 
 * @return None
 */
void dispatch(task* old_task, task* new_task);

#endif //DISPATCHER_H


