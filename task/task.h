/**
 ********************************************************************************
 * @file    task.h
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   Defines the structure of a task.
 ********************************************************************************
 */

#ifndef TASK_H
#define TASK_H

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>
#include "../libc/stdio/stdio.h"
#include "../memory/paging/pager.h"
#include "../memory/frame_allocator.h"


/************************************
 * TYPEDEFS
 ************************************/

/*!
 * @brief Enumeration representing task states
 */
typedef enum
{
    READY,
    RUNNING,
    WAITING
}task_states;


//Struct defining the contents of a task's registers
typedef struct
{
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
}Regs;


//Struct defining a task 
typedef struct task
{
    uint32_t tid;
    Regs registers;
    struct task *next_task;
}task;


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Creates a new tasks
 * @param new_task Task to switch to
 * @param main Pointer to the new task to switch to
 * @param eflags Flags
 * @param virtual_addr_space Pointer to the page directory 
 * @return None
 */
void create_new_task(task* new_task, void (*main)(), uint32_t eflags, uint32_t* virt_addr_space);

/*!
 * @brief Switches the currently running task to a new task 
 * @param task Task to switch to
 */
void switch_state(Regs *old_regs, Regs *new_regs);

/*!
 * @brief Get the contents of the eflags register
 * @return Contents of the eflags register
 */
uint32_t get_eflags(void);

/*!
 * @brief Get the contents of the stack pointer register
 * @return Contents of the esp register
 */
uint32_t get_esp(void);


#endif //TASK_H
