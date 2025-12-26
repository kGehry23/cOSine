/**
 ********************************************************************************
 * @file    string.h
 * @author  Kai Gehry, OSDev Tutorial Reference
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


/*!
 * @brief Copies n bytes from s2 to s1. 
 * @param s1 Address to copy to
 * @param s2 Address to copy from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memcpy(void* restrict s1, const void* restrict s2, size_t n)
{
    //Casts both void pointers to unsigned chars
    unsigned char* dest = (unsigned char*)s1;
    const unsigned char* src = (const unsigned char*)s2;
    
    for(size_t i = 0;i<n;i++)
        dest[i] = src[i];

    return dest;
}

/*!
 * @brief Copies c (converted to unsigned char) into first n bytes of s. 
 * @param s Address to copy to
 * @param c Integer to copy bytes from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memset(void* s, int c, size_t n)
{
    unsigned char* dest = (unsigned char*)s;
    const unsigned char src = (const unsigned char)c;

    for(size_t i = 0;i<n;i++)
        dest[i] = src;
    
    return dest;
}

/*!
 * @brief Copies n bytes from s2 into s1
 * @param s1 Pointer to copy to
 * @param s2 Pointer to copy from
 * @param n Number of bytes to copy 
 * @return Starting address of the copied to memory
 */
void *memmove(void* s1, const void* s2, size_t n)
{
    unsigned char* dest = (unsigned char*)s1;
    const unsigned char* src = (const unsigned char*)s2;

    /*If the source address is larger than the destination address, 
      copying continues downwards from the destination addresses's location
    */
    if(dest < src)
    {
        for(size_t i = 0;i<n;i++)
        {
            dest[i] = src[i];
        }
    }
    /*If the source address is smaller than the destination address, 
      copying continues upwards from the destination addresses's location
    */
    else
    {
        for(size_t i = n;i!=0;i--)
        {
            dest[i-1] = src[i-1];
        }
    }

    return dest;
}





