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

#include <stdarg.h>

#define EOF (-1)

int printf(const char* __restrict, ...);
int putchar(int);
int puts(const char*);



#endif //STDIO_H