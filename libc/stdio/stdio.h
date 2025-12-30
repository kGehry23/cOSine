/**
 ********************************************************************************
 * @file    stdio.h
 *
 * @date    2025-12-24
 *
 * @brief   Header for standard input/output operations.
 *     
 ********************************************************************************
 */

#ifndef STDIO_H
#define STDIO_H

/************************************
 * INCLUDES
 ************************************/
#include <stdarg.h>

/************************************
 * DEFINES
 ************************************/
#define EOF (-1)

/*!
 * @brief Writes a formatted string to the terminal followed by a newline
 * @param data Character array to write to the terminal
 * @return Success code
 */
int printf(const char* __restrict, ...);

/*!
 * @brief Writes a byte to the terminal
 * @param c Byte to write to the terminal as a character
 * @return None
 */
int putchar(int);

/*!
 * @brief Writes the pointed to string to the terminal followed by a newline
 * @param data Character array to write to the terminal
 * @return Success code
 */
int puts(const char*);

#endif //STDIO_H