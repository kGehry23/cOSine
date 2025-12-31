; /**
;  ********************************************************************************
;  * File Name    io.asm
;  *      
;  * Date         2025-12-30
;  *
;  * Brief        Defines the outb and inb functions for essentiual I/O operations
;  *
;  *              Adapted from: https://littleosbook.github.io/book.pdf
;  *              
;  ********************************************************************************
;  */

global _outb
global _inb

; [esp + 8] : second argument passed to externally called outb          
;             Stack pointer + 8 bytes
;
; [esp + 4] : first argument passed to externally called outb
;             Stack pointer + 4 bytes

;writes data to a specified port
_outb:
    mov al, [esp + 8]   ;move the data to be sent into the al register
    mov dx, [esp + 4]   ;move the port address to be sent to into the dx register
    out dx, al          ;write the data to the port
    ret

;returns a byte from a specific port
_inb:
    mov dx, [esp + 4]   ;move port address into dx register
    in al, dx           ;move data from port specified in dx into al
    ret
