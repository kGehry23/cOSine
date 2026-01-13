#include "keyboard.h"


//This would be called when IRQ 1 is triggered, as the interrupt service routine called from asm
void handle_key_press(void)
{
    printf("Test\n");
}
