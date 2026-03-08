/**
 ********************************************************************************
 * @file    task.h
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   Defines the structure of a processs.
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>
#include "../libc/stdio/stdio.h"

//Pointer to task control block of currently running task
extern task_control_block* current_task;

/*!
 * @brief Enumeration representing task states
 */
typedef enum
{
    READY,
    RUNNING,
    WAITING
}task_states;

/*!
 * @brief Struct which represents a task 
 */
typedef struct
{
    void* cr3; //Contents of CR3 register
    void* esp; //Stack pointer
    uint8_t state; //Task state
    uint32_t tid;   //Task identifier
}task_control_block;

/*!
 * @brief Struct which represents a task 
 * @param task Pointer to a task control block
 * @param cr3_reg Contents of the CR3 register
 * @param sp    Contents of the ESP register (stack pointer)
 * @param task_state State of the task
 * @param task_identifier   Unique identifier
 */
void init_task(task_control_block* task, void* cr3_reg, void* sp, uint8_t task_state, uint32_t task_identifier);

/*!
 * @brief Switches the currently running task to a new task 
 * @param task Task to switch to
 */
extern void switch_state(task_control_block* task);
