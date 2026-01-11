/**
 ********************************************************************************
 * @file    stdlib.h
 *
 * @date    2025-12-26
 *
 * @brief   Header for stdlib functions.
 *     
 ********************************************************************************
 */


#include <stddef.h>

#ifndef STDLIB_H
#define STDLIB_H

/*!
 * @brief Causes abnormal process termination to occur
 * @return None
 */
void abort(void);

/*!
 * @brief Allocates memory on the heap
 * @param n Size in bytes of the amount of memory to allocate
 * @return Address of the allocated memory
 */
void* malloc(size_t n);

/*!
 * @brief Frees memory allocated on the heap
 * @param mem_ptr Pointer to the heap memory to allocate
 * @return None
 */
void free(void* mem_ptr);

#endif //STDLIB_H