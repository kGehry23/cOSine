; /**
;  ********************************************************************************
;  * File Name    task.asm
;  * 
;  * Author       Kai Gehry
;  * Date         2026-03-08
;  *
;  * Brief        Defines routines for managing tasks.
;  *          
;  ********************************************************************************
;  */

global _switch_task
global _current_task

_switch_task:
    cli ;disable interrupts

    push ebx ;save base register
    push esi ;source register
    push edi ;destination register
    push ebp ;save stack base pointer