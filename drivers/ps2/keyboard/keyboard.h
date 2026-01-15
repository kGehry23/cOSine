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

/************************************
 * INCLUDES
 ************************************/
#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"
#include "../../../idt/idt.h"
#include "../../../pic/pic.h"

#define BACKSPACE   0x66

#define DATA_PORT   0x60
#define STATUS_PORT 0x64

/*!
 * @brief IRQ handler for IRQ0
 * @return None
 */
void handle_key_press(void);
