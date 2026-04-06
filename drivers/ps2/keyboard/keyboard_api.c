/********************************************************************************
 * @file    keyboard_api.c
 * 
 * @author  Kai Gehry
 * @date    2026-02-26
 *
 * @brief   API to communicate with the keyboard driver
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "keyboard_api.h"

//Keyboard driver variables
extern char input_array[128];
extern uint8_t i;

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
char get_last_char()
{
    return input_array[i-1];
}

/*!
 * @brief Checks if a user's input matches a specified string
 * @return A boolean indicating if the inputs match
 */
bool check_input(const char* input_str)
{
    int comp;
    comp = memcmp(input_str, input_array, strlen(input_str));

    //Reset input character buffer index
    i = 0;

    return (comp == 0 ? true:false);
}