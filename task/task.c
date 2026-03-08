/**
 ********************************************************************************
 * @file    task.c
 * @author  Kai Gehry
 * @date    2026-03-08
 *
 * @brief   Defines the structure of a processs.
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "task.h"

//Initializes a task control block
void init_task(task_control_block* task, void* cr3_reg, void* sp, uint8_t task_state, uint32_t task_identifier)
{
    task->cr3 = cr3_reg;
    task->esp = sp;
    task->state = task_state;
    task->tid = task_identifier;
}