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

#ifndef KEYBOARD_API_H
#define KEYBOARD_API_H

/************************************
 * INCLUDES
 ************************************/
#include "keyboard.h"
#include "string.h"


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
char get_last_char(void);

/*!
 * @brief Returns a subset of the input character buffer
 * @param start_index Starting index to retrieve subset of input array from
 * @return None
 */
void get_subset(uint8_t start_index);

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
bool check_input(const char* input_str);


#endif //KEYBOARD_API_H