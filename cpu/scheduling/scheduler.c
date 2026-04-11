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
#include "../dispatcher/dispatcher.h"


/************************************
* GLOBAL VARIABLES
************************************/
task* current_task;
extern volatile uint32_t test_val;


/************************************
 * FUNCTION PROTOTYPES
 ************************************/
static void run_tasks(task* main, task* task_queue, int num_tasks);


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Performs first come first served scheduling
void fcfs_sched(task *task_queue, int num_tasks)
{
    task main;

    printf("Beginning First Come First Served Scheduling...\n\n");
    //Service tasks in the queue in a first come first served order
    run_tasks(&main, task_queue, num_tasks);
    printf("\n");
}

//Performs round robin scheduling
void sjf_sched(task *task_queue, int num_tasks)
{
    task main;

    task t;
    uint32_t current_min;

    //Selection sort used for selection of task ordering
    for(int i = 0;i<num_tasks-1;i++)
    {
        current_min = i;

        for(int j = i+1;j < num_tasks; j++)
        {
            if(task_queue[j].execution_time < task_queue[current_min].execution_time)
                current_min = j;    
        }

        t = task_queue[current_min];
        task_queue[current_min] = task_queue[i];
        task_queue[i] = t;
    }

    printf("Beginning shortest job first scheduling...\n\n");
    run_tasks(&main, task_queue, num_tasks);
    printf("\n");
}

/*!
 * @brief Runs the tasks organized by the scheduler
 * @param main Task to context switch from 
 * @param task_queue Queue of tasks to dispatch 
 * @param num_tasks Number of tasks to dispatch
 * @return None
 */
static void run_tasks(task* main, task* task_queue, int num_tasks)
{
    for(int i = 0;i<num_tasks;i++)
    {
        task_queue[i].next_task = main;
        current_task = &task_queue[i];
        dispatch(main, &task_queue[i]);
    }
}