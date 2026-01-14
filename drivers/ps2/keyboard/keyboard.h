#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"
#include "../../../idt/idt.h"
#include "../../../pic/pic.h"


//This would be called when IRQ 1 is triggered, as the interrupt service routine called from asm
void handle_key_press();
