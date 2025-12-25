/**
 ********************************************************************************
 * @file    stdio.c
 *
 * @date    2025-12-24
 *
 * @brief   Definitions for standard input/output operations.
 *     
 ********************************************************************************
 */

#include "stdio.h"
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
    va_list list;
    va_start(list, output);

    unsigned int i = 0;

    while(output[i] != '\0')
    {
        if(output[i] == '%')
        {
            i++;

            switch (output[i])
            {
                case 's':
                    terminal_wrestling((const unsigned char*)va_arg(list, char*));
            }

            i++;
        }
        else
        {
            terminal_putchar(output[i]);
            i++;
        }

        
    }

    
    

    return 0;
}