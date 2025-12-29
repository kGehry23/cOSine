; /**
;  ********************************************************************************
;  * File Name    gdt.asm
;  *      
;  * Date         2025-12-28
;  *
;  * Brief        Tells the CPU where the global descriptor table is located,
;  *              and loads the code and data segment registers.
;  *
;  *              Adapted from: OSDev.org and 
;  *              http://www.osdever.net/tutorials/view/the-world-of-protected-mode
;  ********************************************************************************
;  */

global _setGDT
global _reloadSegments

gdtr dw 0
     dd 0 

;tells the cpu where the GDT is located
_setGDT:
    mov ax, [esp + 4]
    mov [gdtr], ax
    mov eax, [esp + 8]
    mov [gdtr + 2], eax
    lgdt [gdtr]
    ret

;loads the data and code segment registers for setup in kernel mode.
;User mode will need to be added later
_reloadSegments: 
     jmp 0x08:reload_CS

reload_CS:
     mov ax, 0x10
     mov ds, ax
     mov es, ax
     mov fs, ax
     mov gs, ax
     mov ss, ax
     ret