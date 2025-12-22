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

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    terminal_initialize();
    terminal_wrestling("Booted into cOSine\n");
    terminal_wrestling("Tab\tTest\n");
    terminal_wrestling("Test2");
}





