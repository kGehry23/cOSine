; /**
;  ********************************************************************************
;  * File Name    task.asm
;  * 
;  * Author       Kai Gehry
;  * Date         2026-03-08
;  *
;  * Brief        Defines routines for managing tasks.
;  *
;  *              Credit: Adapted from
;  *                      https://wiki.osdev.org/Brendan%27s_Multi-tasking_Tutorial
;  *          
;  ********************************************************************************
;  */

global _switch_task
global _current_task

;Create a struct type for the TCB

TCB.sizeof  equ 16 ;reserves 16 bytes for the struct (includes padding)
TCB.esp     equ 0  
TCB.ebx     equ 4 
TCB.cr3     equ 8

;Define a struct which can be accessed with cdecl
_current_task resb TCB.sizeof

_switch_task:
    cli ;disable interrupts

    push ebx 
    push esi 
    push edi 
    push ebp 

    mov edi, [_current_task]  ;moves the task control block of the current task into the edi register
    mov [edi+TCB.esp], esp    ;save the stack pointer of the task into the task's TCB


    mov esi, [esp+20] ;Move the address of the new task into the esi register 
                      ;(The contents of 4 32-bit (4 byte) registers have been pushed, so we access the task_control_block pointer parameters passed to
                      ; switch_task by finding that argument. 4 registers pushed * (4 bytes + 1), where the plus one accounts for the stack pointer being at the
                      ; address above the top stack element).

    ;Set the current task pointer to point to the newly loaded task
    mov [_current_task], esi

    ;Update the stack pointer register with the stack pointer of the new task
    mov esp, [esi+TCB.esp]

    ;top of new task's kernel stack
    mov ebx, [esi+TCB.ebx] 

    ;***STILL NEED TO DEAL WITH TSS***

    ;page directory address for next task
    mov eax, [esi+TCB.cr3]

    ;virtual address space of previous task
    mov ecx, cr3

    ;Ensure whether or not the virtual address space needs to be changed or not
    cmp eax, ecx

    ;when virtual address space does not need to be changed
    je .no_change

    ;change virtual address space if needed
    mov cr3, eax

    .no_change:
        pop ebp
        pop edi
        pop esi
        pop ebx

        ret


    

