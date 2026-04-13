/**
 ********************************************************************************
 * @file    bitmap.c
 * 
 * @author  Kai Gehry
 * @date    2025-12-31
 *
 * @brief   Definitions for the functions on a bitmap structure
 *     
 ********************************************************************************
 */

 
/************************************
* INCLUDES
************************************/
#include "bitmap.h"

/*!
 * @brief Initializes a bitmap
 * @param bmp Pointer to a bitmap structure
 * @return None
 */
void init_bitmap(bitmap_t *bmp)
{
    //Sets all bits in the bitmap to 0
    bmp->bitmap = 0;
}

/*!
 * @brief Sets a bit to 1 in the bitmap
 * @param bmp Pointer to a bitmap structure
 * @param index Index in the bitmap to modify
 * @return None
 */
void set_bit_high(bitmap_t *bmp, uint32_t index)
{
    //oring causes any 0 bits to flip to 1s 
    bmp->bitmap |= (0x1 << index); 
}

/*!
 * @brief Sets a bit to 0 in the bitmap
 * @param bmp Pointer to a bitmap structure
 * @param index Index in the bitmap to modify
 * @return None
 */
void set_bit_low(bitmap_t *bmp, uint32_t index)
{
    bmp->bitmap &= ~(0x1<<index);
}
 
/*!
 * @brief Checks if a bit is set to 1 or 0
 * @param bmp Pointer to a bitmap structure
 * @param index Index in the bitmap to modify
 * @return A boolean indicating if the bit is high 
 */
bool bit_state(bitmap_t *bmp, uint32_t index)
{
    //Bit shift the bitmap and return only a single digit result, 0 or 1
    return (bool)((bmp->bitmap >> index)&(0x1));
}

