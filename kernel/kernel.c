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
#include "libc/stdio.h"

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    terminal_initialize();

    printf("%s\n", "test");
    printf("%s\n", "test5");

}





