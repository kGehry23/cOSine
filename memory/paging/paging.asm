; /**
;  ********************************************************************************
;  * File Name    paging.asm
;  *      
;  * Date         2026-01-17
;  *
;  * Brief        Defines routines to load registers for paging.
;  *          
;  ********************************************************************************
;  */

global _set_cr3
global _get_cr3
global _set_cr0
global _set_cr4

;Moves the address of the page directory into CR3
_set_cr3:
    mov edx, [esp + 4]
    mov cr3, edx
    ret

;Returns the contents of the CR3 register
_get_cr3:
    mov eax, cr3
    ret

;Moves the address of the page directory into CR3
_set_cr0:
    mov ecx, cr0
    mov edx, [esp + 4]
    or edx, ecx
    mov cr0, edx
    ret

;Moves the address of the page directory into CR3
_set_cr4:
    mov edx, [esp + 4]
    mov cr4, edx
    ret
