/**
 ********************************************************************************
 * @file    bitmap.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-31
 *
 * @brief   Header for a bitmap structure
 *     
 ********************************************************************************
 */

/************************************
* INCLUDES
************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t bitmap;

}bitmap_t;

/*!
 * @brief Initializes a bitmap
 * @param bmp Pointer to a bitmap structure
 * @return None
 */
void init_bitmap(bitmap_t *bmp);

/*!
 * @brief Sets a bit to 1 in the bitmap
 * @param bmp Pointer to a bitmap structure
 * @param index Index in the bitmap to modify
 * @return None
 */
void set_bit_high(bitmap_t *bmp, uint32_t index);

/*!
 * @brief Sets a bit to 0 in the bitmap
 * @param bmp Pointer to a bitmap structure
 * @param index Index in the bitmap to modify
 * @return None
 */
void set_bit_low(bitmap_t *bmp, uint32_t index);


