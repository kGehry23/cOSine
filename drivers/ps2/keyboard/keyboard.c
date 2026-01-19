/********************************************************************************
 * @file    keyboard.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-14
 *
 * @brief   Keyboard driver 
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "keyboard.h"
#include "../../../kernel/tty/terminal.h"

//Scan code mappings
char key_codes[] = {
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,
    'q','1',0,0,0,'z','s',
    'a','w','2',0,0,'c','x',
    'd','e','4','3',0,0,' ',
    'v','f','t','r','5',0,0,
    'n','b','h','g','y','6',0,
    0,0,'m','j','u','7','8',
    0,0,',','k','i','o','0',
    '9',0,0,'.','/','l',';',
    'p','-',0,0,0,'\\',0,
    '[','=',0,0,0,0,'\n',
    0,0,0,0,0,0,0,
    0,0,0,0,0,0,0
};

//Character buffer for read characters
char input_array[128];

/*Counter to keep track of current number of characters entered
  before a newline*/
uint8_t i = 0;

/*!
 * @brief IRQ handler for IRQ1
 * @return None
 */
void handle_key_press()
{
    //Checks if a byte is available to read
    if((inb(STATUS_PORT)&0x01) == 1)
    {
        uint32_t reg_contents = inb(DATA_PORT);

        //Checks for multi byte scan codes. Prevents key codes from being reprinted when
        //a key is released
        while((inb(STATUS_PORT)&0x01) == 1)
        {
            reg_contents += inb(DATA_PORT);
        }

        //Converts the scan code to a key code
        if(reg_contents <= sizeof(key_codes)/sizeof(char))
        {
            //Removes previously written text from the terminal if
            if(reg_contents == BACKSPACE)
            {
                terminal_remove_last_character();
                i--;
            }
            else
            {
                input_array[i] = key_codes[reg_contents];
                i++;
                printf("%c", key_codes[reg_contents]);
            }
                
        }
    }

    //Send EOI to PIC
    outb(0x20, 0x20);
}

/*!
 * @brief Returns the last character read from the keyboard
 * @return The last read character
 */
char get_last_char()
{
    char last_char = input_array[i-1];
    return last_char;
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



