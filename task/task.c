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

//Cerates a new task and allocates appropriate memory to the task
void create_new_task(task* new_task, void (*func)(), uint32_t eflags, uint32_t* virt_addr_space)
{
    static uint32_t task_identifier = 0;

    new_task->registers.eax = 0;
    new_task->registers.ebp = 0;
    new_task->registers.ebx = 0;
    new_task->registers.ecx = 0;
    new_task->registers.edi = 0;
    new_task->registers.esi = 0;
    new_task->registers.edx = 0;
    new_task->registers.eflags = eflags;
    new_task->registers.eip = (uint32_t)func;
    new_task->registers.cr3 = (uint32_t)virt_addr_space;
    
    //Need to allocate a page here, then point to the correct location within the page
    uint32_t* frame = allocate_frame();
    new_task->registers.esp = (uint32_t)frame + PAGE_SIZE; //Begin stack at bottom of allocated frame, work way up

    new_task->tid = task_identifier++;
    new_task->next_task = 0;
}