#include "../libc/stdio/stdio.h"
#include "../kernel/tty/terminal.h"
#include "../drivers/ps2/keyboard/keyboard.h"
#include "../io/io.h"
#include <stdbool.h>
#include "shell.h"

const char* man_string = "\n\tSupported commands:\n\n"
                   "\tls - list files and directories\n"
                   "\tcd - change current directory\n"
                   "\tmkdir - create new directory\n"
                   "\ttouch - create new file\n"
                   "\trm - remove file\n"
                   "\tclear - clear terminal contents\n"
                   "\n";


static void display_command_list()
{
    printf("%s", man_string);
}
static void exec_command(void)
{
    if(check_input("man") == true)
        display_command_list();

    else if (check_input("clear") == true)
        terminal_initialize();

    else
        printf("Command not found.\n");
}

void shell_init()
{
    //Clears the terminal 
    terminal_initialize();
    printf("cOSine:$ "); //Prints the shell text
    
    while(1)
    {
        if(get_last_char() == '\n')
        {
            exec_command();
            printf("cOSine:$ ");
        }
        
    }
}
