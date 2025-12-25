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
 * @brief Writes an integer to the terminal
 * @param arg Integer to write to the terminal
 * @return None
 */
static void print_integer(int arg)
{
    int value = arg;
    char string[7];
    unsigned int i = 0;

    while(value >= 10)
    {
        int intermediate = value%10;
        string[i] = intermediate + '0';
        i++;

        value /= 10;
    }

    string[i] = value + '0';

    for(int j = i;j>=0;--j)
    {
        terminal_putchar(string[j]);
    }
}

/*!
 * @brief Writes an integer to the terminal
 * @param arg Integer to write to the terminal
 * @return None
 */
static void print_hex(int arg)
{
    int value = arg;
    char string[8];
    unsigned int i = 0;

    while(value > 0)
    {
        int intermediate = value%16;

        if(intermediate >= 10)
        {
            string[i] = intermediate + 55;
        }
        else
            string[i] = intermediate + '0';

        i++;

        value /= 16;
    }

    string[i] = value + '0';

    terminal_wrestling("0x");

    for(int j = i;j>=0;--j)
    {
        terminal_putchar(string[j]);
    }
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
        //Once a % sign is reached, each argument in the argument list is accessed sequentially
        if(output[i] == '%')
        {
            //Check what next character is to format what is printed to terminal
            switch (output[i+1])
            {
                case 's':
                    terminal_wrestling(va_arg(list, char*));
                    break;
                case 'c':
                    terminal_putchar(va_arg(list,int));
                    break;
                case 'd':
                    print_integer(va_arg(list, int));
                    break;
                case 'p':
                    print_hex(va_arg(list, int));
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