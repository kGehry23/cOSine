/********************************************************************************
 * @file    keyboard.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-14
 *
 * @brief   Header for keyboard driver 
 * 
 ********************************************************************************
*/

#ifndef KEYBOARD_H 
#define KEYBOARD_H 

/************************************
 * INCLUDES
 ************************************/
#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"
#include "../../../idt/idt.h"
#include "../../pic/pic.h"
#include <stdbool.h>


/************************************
 * MACROS
 ************************************/
//Key codes
#define BACKSPACE   0x66

//Ports 
#define DATA_PORT   0x60
#define STATUS_PORT 0x64

/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief IRQ handler for IRQ1
 * @return None
 */
void handle_key_press(void);

#endif //KEYBOARD_H
