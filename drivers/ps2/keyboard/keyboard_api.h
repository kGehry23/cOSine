/********************************************************************************
 * @file    keyboard_api.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-14
 *
 * @brief   Function prototypes or API to communicate with the keyboard driver 
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "keyboard.h"
#include "../../../libc/string/string.h"

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
char get_last_char(void);

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
bool check_input(const char* input_str);