#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"

//Scan code 2 used by default, and is what is currently configured. This driver will focus on scancode 2.
//Can make this more versatile later

//Need to first define scan codes here, then design key codes

#define RELEASE_1   0xF0
#define A_PRESSED   0x1C
#define A_RELEASED  (RELEASE_1 + A_PRESSED)

//Random size
char mappings[1024];

//Just an example of how this could be mapped. Likely not the best way to do this... maybe implement some kind of subtraction as well?
void init_mappings()
{
    mappings[A_PRESSED] = 'A';
}

//This would be called when IRQ 1 is triggered, as the interrupt service routine called from asm
void handle_key_press(void);
