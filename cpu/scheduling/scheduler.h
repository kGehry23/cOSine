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
#include "task.h"
#include "pit.h"


/************************************
* FUNCTION PROTOTYPES
************************************/

/*!
 * @brief Performs first come first served scheduling
 * @param task_queue Queue of tasks to schedule 
 * @param num_tasks Number of tasks to schedule
 * @return None
 */
void fcfs_sched(task *task_queue, uint32_t num_tasks);

/*!
 * @brief Performs shortest job first scheduling
 * @param task_queue Queue of tasks to schedule 
 * @param num_tasks Number of tasks to schedule
 * @return None
 */
void sjf_sched(task *task_queue, uint32_t num_tasks);

/*!
 * @brief Performs round robin scheduling
 * @param task_queue Queue of tasks to schedule 
 * @param num_tasks Number of tasks to schedule
 * @return None
 */
void rr_sched(task *task_queue, uint32_t num_tasks);

#endif //SCHEDULER_H