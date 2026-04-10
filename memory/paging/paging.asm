; /**
;  ********************************************************************************
;  * File Name    paging.asm
;  * 
;  * Author       Kai Gehry
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

global _enable_paging
global _load_page_dir

;Moves the address of the page directory into CR3
_set_cr3:
    mov edx, [esp + 4]
    mov cr3, edx
    ret

;Returns the contents of the CR3 register
_get_cr3:
    mov eax, cr3
    ret

;Sets the contents of the CR0 register. In the case of enabling paging
;the 31st bit needs to be set high
_set_cr0:
    mov ecx, cr0
    mov edx, [esp + 4]
    or edx, ecx ;retain original contents, and set new bits high
    mov cr0, edx
    ret

;Sets the contents of the CR4 register
_set_cr4:
    mov edx, [esp + 4]
    mov cr4, edx
    ret


; _load_page_dir:
;     push edx
;     mov edx, esp
;     mov eax, [esp+8]
;     mov cr3, eax
;     mov esp, edx
;     pop edx
;     ret

; _enable_paging:
;     push ebp
;     mov ebp, esp
;     mov eax, cr0
;     or eax, 0x80000000
;     mov cr0, eax
;     mov esp, ebp
;     pop ebp
;     ret



