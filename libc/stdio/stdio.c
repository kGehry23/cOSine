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
#include "../../kernel/tty/terminal.h"

/************************************
 * DEFINES
 ************************************/
#define INT_BASE 10
#define HEX_BASE 16
#define POINTER_SIZE 8
#define HEX_LETTER_BASE 55
#define ASCII_TO_INT_BASE 48

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
 * @brief Writes a byte to the terminal
 * @param c Byte to write to the terminal as a character
 * @return None
 */
int putchar(int c)
{
    char c_char = (char)c;
    terminal_putchar(c_char);
}

/*!
 * @brief Writes an integer to the terminal
 * @param arg Integer to write to the terminal
 * @return None
 */
static void print_integer(int arg)
{
    int value = arg;
    char string[POINTER_SIZE-1];
    unsigned int i = 0;

    while(value >= INT_BASE)
    {
        int intermediate = value%INT_BASE;
        string[i] = intermediate + ASCII_TO_INT_BASE;
        i++;

        //Multiplication by 0.1 more efficient than division by 10
        value *= 0.1;
    }

    string[i] = value + ASCII_TO_INT_BASE;

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
    char string[POINTER_SIZE];
    unsigned int i = 0;

    while(value > 0)
    {
        int intermediate = value%HEX_BASE;

        if(intermediate >= 10)
        {
            string[i] = intermediate + HEX_LETTER_BASE;
        }
        else
            string[i] = intermediate + ASCII_TO_INT_BASE;

        i++;

        //Bit shift by 16 (2^4). More efficient than direct division by 16
        value >>= 4;
    }

    string[i] = value + ASCII_TO_INT_BASE;

    printf("0x");

    //Calculate remaining positions that have not been filled
    int fill = POINTER_SIZE-i;

    //Fill LSBs with '0''s.
    for(int j = 0;j<fill-1;j++)
    {
        terminal_putchar('0');
    }

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