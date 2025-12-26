/**
 ********************************************************************************
 * @file    kernel.c
 *
 * @date    2025-12-20
 *
 * @brief   Basic kernel code.
 * 
 *          Credit: Adapted from https://wiki.osdev.org/Bare_Bones
 *      
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdbool.h>
#include "terminal/terminal.h"
#include "../libc/stdio/stdio.h"
#include "../libc/stdlib/stdlib.h"

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    int t = (int)0xB8000;
    int i = 10;
    int *p = &i;

    terminal_initialize();
    printf("This is a %s and this is a hex number: %p. This is a character: %c.\n", "test", p,'a');
    puts("This the output from puts()");

}





