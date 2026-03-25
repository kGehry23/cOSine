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
;  *                      and 
;  *                      https://wiki.osdev.org/Cooperative_Multitasking
;  *                      https://en.wikibooks.org/wiki/X86_Assembly/Other_Instructions
;  *
;  ********************************************************************************
;  */

;The following assembly routine is heavily commented (for my own depth of understanding)

global _switch_state

_switch_state:

    ;Save old context

    ;1. Push all general purpose registers in order eax->ecx->ebx->esp->ebp->esi->edi
    ;2. Push the contents of the eflags register 
    ;3. Push the contents of the cr3 register onto the stack (for virtual address space)

    pusha
    pushf 
    mov eax, cr3
    push eax

    ;Save the contents of the general purpose registers
    mov eax, [esp + 44] ;Navigate to beginning of the old task's registers (to save)
    mov [eax + 4], ebx
    mov [eax + 8], ecx
    mov [eax + 12], edx
    mov [eax + 16], esi
    mov [eax + 20], edi

    ;Save old stack pointer
    mov ebx, [esp + 24] 
    mov [eax + 24], ebx

    ; Save stack base register
    mov [eax + 28], ebp

    ;Save instruction pointer (originally stored in eax register when pushed)
    mov esi, [esp + 40]
    mov [eax + 32], esi

    ;Saves the contents of the cr3 register
    mov ecx, [esp + 4]
    mov [eax + 40], ecx

    ;Saves the contents of the eflags register
    mov edx, [esp + 8]
    mov [eax + 36], edx

    ;Load new context
    mov eax, [esp + 48]
    
    ;Load general purpose registers, stack pointer and stack base pointer
    mov ebx, [eax + 4]
    mov ecx, [eax + 8]
    mov edx, [eax + 12]
    mov esi, [eax + 16]
    mov edi, [eax + 20]
    mov esp, [eax + 24]
    mov ebp, [eax + 28]

    ; ; Deals with eflags 
    ; push eax
    ; mov eax, [eax + 36] 
    ; push eax
    ; popf
    ; pop eax

    ; Deals with cr3
    ;
    ;1. Push contents of eax register
    ;2. Move new cr3 contents into eax
    ;3. Move new cr3 contents into cr3 register
    ;4. Pop old eax contents from stack (back into eax register)
    push eax
    mov eax, [eax + 40]
    mov cr3, eax
    pop eax


    ; Deals with instruction pointer
    ;1. Push contents of eax register
    ;2. Move new instruction pointer contents into eax
    ;3. Use xchg to set the stack pointer to point to the instruction pointed to 
    ;   by the instruction pointer
    ;4. Point eax to the instruction pointer
    push eax
    mov eax, [eax + 32]
    xchg eax, [esp]
    mov eax, [eax]

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


    

