/**
 ********************************************************************************
 * @file    scheduler.c
 * 
 * @author  Kai Gehry
 * @date    2025-03-29
 *
 * @brief   Scheduler function prototypes and defines.
 *     
 ********************************************************************************
 */

/************************************
* INCLUDES
************************************/
#include "scheduler.h"


/************************************
* GLOBAL VARIABLES
************************************/
task* current_task;
extern volatile uint32_t test_val;


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Performs first come first served scheduling
void fcfs_sched(task *task_queue, int num_tasks)
{
    task main;

    printf("Beginning First Come First Served Scheduling...\n\n");

    //Service tasks in the queue in a first come first served order
    for(int i = 0;i<num_tasks;i++)
    {
        task_queue[i].next_task = &main;
        current_task = &task_queue[i];
        switch_state(&main.registers, &(task_queue[i].registers));
    }

    printf("\n");
}

//Performs round robin scheduling
void rr_sched(task *task_queue, int num_tasks, uint32_t time_quantum)
{
    task main;

    printf("Beginning Round Robin Scheduling...\n\n");

    //of course does nothing of use rn for this type of scheduling

    // //Service tasks in the queue in a first come first served order
    // for(int i = 0;i<num_tasks;i++)
    // {
    //     task_queue[i].next_task = &main;
    //     current_task = &task_queue[i];
    //     switch_state(&main.registers, &(task_queue[i].registers));
    // }

    printf("\n");
}