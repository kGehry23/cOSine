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
#include "dispatcher.h"


/************************************
* GLOBAL VARIABLES
************************************/
task* current_task;
extern volatile uint32_t test_val;


/************************************
 * FUNCTION PROTOTYPES
 ************************************/
static void dispatch_tasks(task* main, task* task_queue, uint32_t num_tasks);


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Performs first come first served scheduling
void fcfs_sched(task *task_queue, uint32_t num_tasks)
{
    task main;

    printf("Beginning First Come First Served Scheduling...\n\n");
    //Service tasks in the queue in a first come first served order
    dispatch_tasks(&main, task_queue, num_tasks);
    printf("\n");
}

//Performs shortest job first scheduling
void sjf_sched(task *task_queue, uint32_t num_tasks)
{
    task main; 

    task t;
    uint32_t current_min;

    //Selection sort used for correct task ordering
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
    dispatch_tasks(&main, task_queue, num_tasks);
    printf("\n");
}

//Performs round robin scheduling
void rr_sched(task *task_queue, uint32_t num_tasks)
{
    task main;

    //Tracks circular queue index
    uint32_t i = 0;
    uint32_t terminated = 0;

    printf("Beginning round robin scheduling...\n\n");

    //Continues until all tasks have completed their execution 
    while(terminated < num_tasks)
    {
        if(task_queue[i].state != TERMINATED)
        {
            task_queue[i].next_task = &main;
            current_task = &task_queue[i];
            dispatch(&main, &task_queue[i]);

            //Keep track of the number of tasks that have been terminated
            if(task_queue[i].state == TERMINATED)
                terminated++;
        }

        //Recalculates index
        i = (i+1)%num_tasks;
    }

    printf("\n");
}

/*!
 * @brief Runs the tasks organized by the scheduler
 * @param main Task to context switch from 
 * @param task_queue Queue of tasks to dispatch 
 * @param num_tasks Number of tasks to dispatch
 * @return None
 */
static void dispatch_tasks(task* main, task* task_queue, uint32_t num_tasks)
{
    for(int i = 0;i<num_tasks;i++)
    {
        task_queue[i].next_task = main;
        current_task = &task_queue[i];
        dispatch(main, &task_queue[i]);
    }
}