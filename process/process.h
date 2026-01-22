/**
 ********************************************************************************
 * @file    process.h
 * @author  Kai Gehry
 * @date    2026-01-18
 *
 * @brief   Defines the structure of a processs.
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdio.h>
#include <stdint.h>

/*!
 * @brief Struct which represents a process
 * @param pid Process identifier
 */
typedef struct
{
    uint32_t pid;

} process;
