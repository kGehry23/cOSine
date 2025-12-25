/**
 ********************************************************************************
 * @file    stdio.c
 * 
 * @author  Kai Gehry
 * @date    2025-12-24
 *
 * @brief   Definitions for standard input/output operations.
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "stdio.h"
#include "string.h"
#include "../../kernel/terminal/terminal.h"

/*!
 * @brief Writes the pointed to string to the terminal followed by a newline
 * @param data Character array to write to the terminal
 * @return Success code
 */
int puts(const char* str_data)
{
    return printf("%s\n", str_data);
}

/*!
 * @brief Writes a formatted string to the terminal followed by a newline
 * @param data Character array to write to the terminal
 * @return Success code
 */
int printf(const char* output, ...)
{
    //List of arguments
    va_list list;
    //Initialize the list
    va_start(list, output);

    //Integer to keep track of current string index
    unsigned int i = 0;

    //Continue iterating until null terminating character is reached
    while(output[i] != '\0')
    {
        //Once a % sign is reached, each argument in the argument list is accessed sequentially
        if(output[i] == '%')
        {
            //Check what next character is to format what is printed to terminal
            switch (output[i+1])
            {
                case 's':
                    terminal_wrestling(va_arg(list, char*));
                    break;
                case 'd':
                    //Convert intended integer to correct character
                    terminal_putchar(va_arg(list, int) + '0');
                    break;
                case 'c':
                    terminal_putchar(va_arg(list,int));
                    break;
            }

            i = i + 2;
        }
        else
        {
            //If no format specifier encountered, simply place character in terminal
            terminal_putchar(output[i]);
            i++;
        }

        
    }

    //Free memory allocated for va_list
    va_end(list);

    return 0;
}