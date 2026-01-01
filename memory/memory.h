/**
 ********************************************************************************
 * @file    memory.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-31
 *
 * @brief   Defines standard dynamic memory functions for use by the kernel
 *     
 ********************************************************************************
 */

#ifndef MEMORY_H
#define MEMORY_H

/************************************
* INCLUDES
************************************/
#include <stddef.h>

/************************************
 * DEFINES
 ************************************/
//Sample for now, does not need to be actual page size used
#define PAGE_SIZE 4096 //4KiB page size

/*!
 * @brief Allocates memory for the kernel
 * @param n Size in bytes of memory to allocate
 * @return Pointer to allocated memory
 */
void* k_malloc(size_t n);

/*!
 * @brief Frees memory allocated for the kernel
 * @param mem_ptr Pointer to the allocated memory
 * @return None
 */
void k_free(void* mem_ptr);

#endif //MEMORY_H