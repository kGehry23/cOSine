/**
 ********************************************************************************
 * @file    scheduler.h
 * 
 * @author  Kai Gehry
 * @date    2025-03-29
 *
 * @brief   Scheduler function prototypes and defines.
 *     
 ********************************************************************************
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

/************************************
* INCLUDES
************************************/
#include "../../task/task.h"
#include "../../drivers/pit/pit.h"


/************************************
* FUNCTION PROTOTYPES
************************************/

/*!
 * @brief Performs first come first served scheduling
 * @param task_queue Queue of tasks to schedule 
 * @param num_tasks Number of tasks to schedule
 * @return None
 */
void fcfs_sched(task *task_queue, int num_tasks);

/*!
 * @brief Performs round robin scheduling
 * @param task_queue Queue of tasks to schedule 
 * @param num_tasks Number of tasks to schedule
 * @return None
 */
void rm_sched(task *task_queue, int num_tasks);

#endif //SCHEDULER_H