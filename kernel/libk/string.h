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

/*!
 * @brief Returns the number of elements in a provided character array
 * @param str Character pointer to check length of
 * @return Length of the pointed to character array
 */
size_t strlen(const char* str);

/*!
 * @brief Compares the first n bytes of of s1 to the first n bytes of s2
 * @param s1 First pointer in comparison
 * @param s2 Second pointer in comparison
 * @param n Number of bytes to compare
 * @return An integer greater than, equal to, or less than 0.
 */
int memcmp(const void *s1, const void *s2, size_t n);


void *memcpy(void* __restrict, const void* restrict, size_t);
void *memmove(void*, const void*, size_t);
void *memset(void*, int, size_t);
size_t strlen(const char*);


#endif //STRING_H