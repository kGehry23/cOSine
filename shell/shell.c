/********************************************************************************
 * @file    shell.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   cOSine shell
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

//Buffer for previously entered commands
char* cmd_arr[128];

//Command list string
const char* man_string = "\n\tSupported commands:\n\n"
                   "\tls - list directory contents\n"
                   "\tcd - change current directory\n"
                   "\tmkdir - create new directory\n"
                   "\ttouch - create new file\n"
                   "\trm - delete file\n"
                   "\tcat - display contents of file\n"
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

    else if (check_input("clear") == true || check_input("cls") == true)
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
    printf("cOSh:$ ");
    
    while(1)
    {
        if(get_last_char() == '\n')
        {
            exec_command();
            printf("cOSh:$ ");
        }
        
    }
}
