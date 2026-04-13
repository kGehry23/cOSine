/**
 ********************************************************************************
 * @file    string.h
 *
 * @date    2025-12-24
 *
 * @brief   Header for string operations.
 *     
 ********************************************************************************
 */

#ifndef STRING_H
#define STRING_H

/************************************
 * INCLUDES
 ************************************/
#include <stddef.h>


/************************************
* FUNCTION PROTOTYPES
************************************/

/*!
 * @brief Returns the number of elements in a provided character array
 * @param str Character pointer to check length of
 * @return Length of the pointed to character array
 */
size_t strlen(const char*);

/*!
 * @brief Compares the first n bytes of of s1 to the first n bytes of s2
 * @param s1 First pointer in comparison
 * @param s2 Second pointer in comparison
 * @param n Number of bytes to compare
 * @return An integer greater than, equal to, or less than 0.
 */
int memcmp(const void *s1, const void *s2, size_t n);

/*!
 * @brief Copies n bytes from s2 to s1. 
 * @param s1 Address to copy to
 * @param s2 Address to copy from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memcpy(void* __restrict, const void* restrict, size_t);

/*!
 * @brief Copies c (converted to unsigned char) into first n bytes of s. 
 * @param s Address to copy to
 * @param c Integer to copy bytes from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memset(void*, int, size_t);

/*!
 * @brief Copies n bytes from s2 into s1
 * @param s1 Pointer to copy to
 * @param s2 Pointer to copy from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memmove(void*, const void*, size_t);


#endif //STRING_H