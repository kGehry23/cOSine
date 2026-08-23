/**
 ********************************************************************************
 * @file    stdint.h
 * @author  Kai Gehry
 * @date    2026-08-23
 * @brief
 ********************************************************************************
 */

#ifndef STDINT_H
#define STDINT_H

/************************************
 * INCLUDES
 ************************************/

/************************************
 * MACROS AND DEFINES
 ************************************/

/************************************
 * TYPEDEFS
 ************************************/

/* Unsigned types */
typedef unsigned char           uint8_t;
typedef unsigned short          uint16_t;
typedef unsigned int            uint32_t;
typedef unsigned long long      uint64_t;

/* Signed types */
typedef signed char             int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long               int64_t;

/* Floating point types */
typedef float                   float32_t;
typedef double                  float64_t;

/* Pointer types */
typedef int                     intptr_t;
typedef unsigned int            uintptr_t;


/************************************
 * GLOBAL FUNCTION PROTOTYPES
 ************************************/

#endif //STDINT_H