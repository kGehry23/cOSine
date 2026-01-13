; /**
;  ********************************************************************************
;  * File Name    idt.asm
;  *      
;  * Date         2025-12-28
;  *
;  * Brief        Initializes the IDT and assigns ISR stubs.
;  *
;  *              Adapted from: OSDev.org and 
;  *              http://www.osdever.net/tutorials
;  ********************************************************************************
;  */

global _setIDT
global _isr_stub_table
global _irq_stub_table

%macro isr_err_stub 1
isr_stub_%+%1:
    call _exception_handler
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    call _exception_handler
    iret
%endmacro

%macro isr_stub 1
isr_stub_%+%1:
    pushad
    cld
    call _interrupt_handler
    popad
    iret
%endmacro

;Uses the exception handler function defined in idt.c
extern _exception_handler
;Externally called generic interrupt handler function
extern _interrupt_handler

;Table of isrs
isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31
isr_stub 32
isr_stub 33
isr_stub 34
isr_stub 35
isr_stub 36
isr_stub 37
isr_stub 38
isr_stub 39
isr_stub 40
isr_stub 41
isr_stub 42
isr_stub 43
isr_stub 44
isr_stub 45
isr_stub 46
isr_stub 47

;isr stub table which is called externally
_isr_stub_table:
%assign i 0
%rep    48
    dd isr_stub_%+i
%assign i i+1
%endrep


;IDTR structure used to load base and limit
idtr dw 0
     dd 0 

;Tells the cpu where the idt is located
_setIDT:
    cli   ;disables all interrupts
    mov ax, [esp + 4]
    mov [idtr], ax
    mov eax, [esp + 8]
    mov [idtr + 2], eax
    lidt [idtr]
    ret









