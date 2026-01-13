#include "keyboard.h"

//Just an example of how this could be mapped. Likely not the best way to do this... maybe implement some kind of subtraction as well?
void init_mappings()
{
    mappings[A_PRESSED].key = 'a';
    mappings[W_PRESSED].key = 'w';
    mappings[S_PRESSED].key = 's';
}

//This would be called when IRQ 1 is triggered, as the interrupt service routine called from asm
void handle_key_press(void)
{
    if(inb(0x64)&0x1 == 1)
    {
        printf("%p",inb(0x60));
    }
        
    // printf("Interrupt\n");
    PIC_eoi(1);
}
