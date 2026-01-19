/********************************************************************************
 * @file    shell.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   cOSine shell (cOSh -> hyperbolic cos)
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "../libc/stdio/stdio.h"
#include "../kernel/tty/terminal.h"
#include "../drivers/ps2/keyboard/keyboard.h"
#include "shell.h"

//Command list string
const char* man_string = "\n\tSupported commands:\n\n"
                   "\tls - list files and directories\n"
                   "\tcd - change current directory\n"
                   "\tmkdir - create new directory\n"
                   "\ttouch - create new file\n"
                   "\trm - remove file\n"
                   "\tclear - clear terminal contents\n"
                   "\n";


                   
/*!
 * @brief Displays the command list
 * @return None
 */
static void display_command_list()
{
    printf("%s", man_string);
}

/*!
 * @brief Executes an entered command
 * @return None
 */
static void exec_command(void)
{
    if(check_input("man") == true)
        display_command_list();

    else if (check_input("clear") == true)
        terminal_initialize();
    
    // else if(check_input("echo") == true)
    //     printf("%s\n", arr());

    else
        printf("Command not found.\n");
}

/*!
 * @brief Initializes and starts cOSh
 * @return None
 */
void shell_init()
{
    //Clears the terminal 
    terminal_initialize();
    printf("cOSine:$ ");
    
    while(1)
    {
        if(get_last_char() == '\n')
        {
            exec_command();
            printf("cOSine:$ ");
        }
        
    }
}
