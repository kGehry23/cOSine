global _outb
;global _inb

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


