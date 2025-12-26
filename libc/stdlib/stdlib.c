/**
 ********************************************************************************
 * @file    stdlib.c
 *
 * @date    2025-12-26
 *
 * @brief   Definitions for stdlib functions.
 *     
 ********************************************************************************
 */

 /************************************
 * INCLUDES
 ************************************/
#include "stdlib.h"
#include "../stdio/stdio.h"

/*!
 * @brief Causes abnormal process termination to occur
 * @return None
 */
void abort(void)
{
    printf("kernel: panic: abort()\n");
    //Inline assembly to halt hte CPU
    asm volatile( "hlt" );
}