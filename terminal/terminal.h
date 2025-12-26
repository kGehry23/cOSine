/**
 ********************************************************************************
 * @file    terminal.h
 *
 * @date    2025-12-21
 *
 * @brief   Header for terminal writing/character placement and VGA setup.
 * 
 *          Credit: Adapted from https://wiki.osdev.org/Bare_Bones
 *      
 ********************************************************************************
 */

#ifndef TERMINAL_H
#define TERMINAL_H

/************************************
 * INCLUDES
 ************************************/
#include <stddef.h>
#include <stdint.h>

/*!
 * @brief Clears the terminal window
 * @return None
 */
void terminal_initialize(void);

/*!
 * @brief Sets the background colour of the terminal
 * @param colour Unsigned 8 bit integer representing the terminal background colour
 * @return None
 */
void terminal_setcolour(uint8_t colour);

/*!
 * @brief Places a character at a specified location in the terminal
 * @param c Character to write to the terminal
 * @param colour Colout of the character to write
 * @param x Row index of VGA memory
 * @param y Column index of VGA memory
 * @return None
 */
void terminal_putentryat(char c, uint8_t colour, size_t x, size_t y);

/*!
 * @brief Places the specified character in the terminal window
 * @param c Character to write to the terminal
 * @return None
 */
void terminal_putchar(char c);


/*!
 * @brief Writes a string of characters to the terminal
 * @param data Character array to write to the terminal
 * @param size Number of elements in the character array
 * @return None
 */
void terminal_write(const char* data, size_t size);


/*!
 * @brief Writes a string of characters to the terminal
 * @param data Character array to write to the terminal
 * @return None
 */
void terminal_wrestling(const char* data);


#endif //TERMINAL_H