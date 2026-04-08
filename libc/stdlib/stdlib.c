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


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

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

//Allocates memory on a processes' heap
void* malloc(size_t n)
{

}

//Frees memory allocated on a processes' heap
void free(void *mem_ptr)
{   

}


