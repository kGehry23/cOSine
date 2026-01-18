#include "../libc/stdio/stdio.h"
#include "../kernel/tty/terminal.h"
#include "../drivers/ps2/keyboard/keyboard.h"
#include "../io/io.h"
#include "shell.h"

void shell_init()
{
    //Clears the terminal 
    terminal_initialize();
    printf("cOSine:$ "); //Prints the shell text... does noting currently
    
    while(1)
    {
        if(get_last_char() == '\n')
        {
            printf("cOSine:$ ");
        }
        
    }
}