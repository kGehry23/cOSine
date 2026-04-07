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


/************************************
 * GLOBAL AND STATIC VARIABLES
 ************************************/

//Keyboard driver variables
extern uint8_t i;
extern char input_array[128];


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
char get_last_char()
{
    return input_array[i-1];
}

//Gets subset of input character buffer
void get_subset(uint8_t start_index)
{
    while(input_array[start_index])
    {
        printf("%c", input_array[start_index]);
        start_index++;
    }

    //Clear populated indices of input array
    memset(input_array, 0, start_index);
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