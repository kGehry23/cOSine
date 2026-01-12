extern _handle_key_press 
global _isr_handle
align  4

_isr_handle:
    pushad
    cld
    call _handle_key_press
    popad
    iret