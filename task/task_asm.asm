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

global _switch_state
; global _current_task

;Create a struct type for the task 
REGS.sizeof     equ 44
REGS.eax        equ 0
REGS.ebx        equ 4
REGS.ecx        equ 8
REGS.edx        equ 12
REGS.esi        equ 16 
REGS.edi        equ 20 
REGS.esp        equ 24
REGS.ebp        equ 28
REGS.eip        equ 32
REGS.eflags     equ 36
REGS.cr3        equ 40


; old_regs resb REGS.sizeof
; new_regs resb REGS.sizeof

; TCB.sizeof  equ 16 ;reserves 16 bytes for the struct (includes padding)
; TCB.esp     equ 0  
; TCB.ebx     equ 4 
; TCB.cr3     equ 8

; ;Define a struct which can be accessed with cdecl


_switch_state:
    ; cli ;disable interrupts

    ; push edi

    ;Save contents of registers to register struct of old task
    ; mov edi, [old_regs]
    ; mov [edi+REGS.eax], eax
    ; mov [edi+REGS.ebx], ebx
    ; mov [edi+REGS.ecx], ecx
    ; mov [edi+REGS.edx], edx
    ; mov [edi+REGS.esi], esi
    ; ; mov [edi+REGS.edi], edi
    ; mov [edi+REGS.esp], esp
    ; mov [edi+REGS.ebp], ebp
    ; mov [edi+REGS.eip], eip
    ; mov [edi+REGS.eflags], flags 

    ; mov [edi+REGS.cr3], cr3

    ;load register contents of new task
    mov eax, [esp + 4]
    mov edx, [esp + 8]

    push ebp
    push ebx
    push esi
    push edi

    mov eax, esp
    mov esp, edx

    pop edi
    pop esi
    pop ebx
    pop ebp
    ret






















    ; mov eax, [edi+REGS.eax]
    ; mov ebx, [eax+REGS.ebx]
    ; mov ecx, [eax+REGS.ecx]
    ; mov edx, [eax+REGS.edx]
    ; mov esi, [eax+REGS.esi]
    ; ; mov [edi+REGS.edi], edi
    ; mov esp, [eax+REGS.esp]
    ; mov ebp, [eax+REGS.ebp]
    ; mov eax, [eax+REGS.eip]
    ; ; push eax
    ; jmp eax

    ; mov eax, [edi+REGS.cr3]
    ; mov flags, [edi+REGS.eflags]
    ; mov cr3, eax

    

    


;     push ebx 
;     push esi 
;     push edi 
;     push ebp 

;     mov edi, [_current_task]  ;moves the task control block of the current task into the edi register
;     mov [edi+TCB.esp], esp    ;save the stack pointer of the task into the task's TCB


;     mov esi, [esp+20] ;Move the address of the new task into the esi register 
;                       ;(The contents of 4 32-bit (4 byte) registers have been pushed, so we access the task_control_block pointer parameters passed to
;                       ; switch_task by finding that argument. 4 registers pushed * (4 bytes + 1), where the plus one accounts for the stack pointer being at the
;                       ; address above the top stack element).

;     ;Set the current task pointer to point to the newly loaded task
;     mov [_current_task], esi

;     ;Update the stack pointer register with the stack pointer of the new task
;     mov esp, [esi+TCB.esp]

;     ;top of new task's kernel stack
;     mov ebx, [esi+TCB.ebx] 

;     ;***STILL NEED TO DEAL WITH TSS***

;     ;page directory address for next task
;     mov eax, [esi+TCB.cr3]

;     ;virtual address space of previous task
;     mov ecx, cr3

;     ;Ensure whether or not the virtual address space needs to be changed or not
;     cmp eax, ecx

;     ;when virtual address space does not need to be changed
;     je .no_change

;     ;change virtual address space if needed
;     mov cr3, eax

;     .no_change:
;         pop ebp
;         pop edi
;         pop esi
;         pop ebx

;         ret


    

