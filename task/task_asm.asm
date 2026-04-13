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
global _get_eflags
global _get_esp

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

    ; Store contents of eax register 
    mov edi, [esp + 36]
    mov [eax], edi

    ;Save old stack pointer
    mov ebx, [esp + 20] 
    add ebx, 0x04 
    mov [eax + 24], ebx

    ; Save stack base register
    mov ebp, [esp + 16]
    mov [eax + 28], ebp

    ;Save instruction pointer (originally stored in eax register when pushed)
    mov esi, [esp + 40]
    mov [eax + 32], esi

    ; ;Saves the contents of the cr3 register
    pop ebx
    mov [eax + 40], ebx
    push ebx

    ;Saves the contents of the eflags register
    mov edx, [esp + 4]
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
    push eax
    mov eax, [eax + 36] 
    push eax
    popf
    pop eax

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
    ;4. 
    push eax
    mov eax, [eax + 32]
    xchg eax, [esp]
    mov eax, [eax]

    ret

; Returns the contents of the eflags register
_get_eflags:
    pushf
    pop eax
    ret

; Returns the contents of the eflags register
_get_esp:
    mov eax, esp
    ret


