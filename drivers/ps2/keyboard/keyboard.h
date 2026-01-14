#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"
#include "../../../idt/idt.h"
#include "../../../pic/pic.h"

//Scan code 2 used by default, and is what is currently configured. This driver will focus on scancode 2.
//Can make this more versatile later

//Need to first define scan codes here, then design key codes
#define IRQ_NUMBER  1

#define PS2_READ_WRITE_DATA_PORT 0x60
#define PS2_READ_STATUS_PORT 0x64
#define PS2_WRITE_COMMAND_PORT 0x64

#define RELEASE_1   0xF0

#define A_PRESSED   0x1C
#define W_PRESSED   0x1D
#define S_PRESSED   0x1B

#define A_RELEASED  (RELEASE_1 + A_PRESSED)


//Just an example of how this could be mapped. Likely not the best way to do this... maybe implement some kind of subtraction as well?
void init_mappings();

//This would be called when IRQ 1 is triggered, as the interrupt service routine called from asm
void handle_key_press();
