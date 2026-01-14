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

/*!
 * @brief IRQ handler for IRQ0
 * @return None
 */
void handle_key_press(void);
