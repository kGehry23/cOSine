/**
 ********************************************************************************
 * @file    string.h
 *
 * @date    2025-12-24
 *
 * @brief   Defines string operations.
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "string.h"

/*!
 * @brief Returns the number of elements in a provided character array
 * @param str Character pointer to check length of
 * @return Length of the pointed to character array
 */
size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

/*!
 * @brief Compares the first n bytes of of s1 to the first n bytes of s2
 * @param s1 First pointer in comparison
 * @param s2 Second pointer in comparison
 * @param n Number of bytes to compare
 * @return An integer greater than, equal to, or less than 0.
 */
int memcmp(const void *s1, const void *s2, size_t n)
{
    for(size_t i = 0; i<n; i++)
    {
        //1 is returned if s1 is greater than s2
        if(((const unsigned char *)s1)[i] > ((const unsigned char *)s2)[i])
            return 1;
        //-1 is returned if s2 is greater than s1
        else if(((const unsigned char *)s1)[i] < ((const unsigned char *)s2)[i])
            return -1;
    }

    return 0;
}






