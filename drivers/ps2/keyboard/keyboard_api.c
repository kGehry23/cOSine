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
    return input_array[i-1];;
}

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
bool check_input(const char* input_str)
{
    uint8_t counter = 0;
    uint8_t j = 0;

    while(input_str[j] != '\0')
    {
        if(input_str[j] == input_array[j])
        {
            counter++;
        }
        j++;
    }

    i = 0;

    if(counter == j)
        return true;
    else
        return false; 
}