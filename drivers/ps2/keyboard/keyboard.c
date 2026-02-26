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
#include "keyboard.h"
#include "../../../kernel/tty/terminal.h"

/*Counter to keep track of current number of characters entered
  before a newline*/
uint8_t i = 0;
//Character buffer for read characters
char input_array[128];

//Scan code mappings
static char key_codes[] = {
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
            reg_contents += inb(DATA_PORT);

        //Converts the scan code to a key code
        if(reg_contents <= sizeof(key_codes)/sizeof(char))
        {
            //Removes previously written text from the terminal if
            if(reg_contents == BACKSPACE)
            {
                terminal_remove_last_character();
                i--;
                //return 0;
            }
            else
            {
                input_array[i] = key_codes[reg_contents];
                i++;
                //return key_codes[reg_contents];
                printf("%c", key_codes[reg_contents]);
            }
                
        }
    }

    //Send EOI to PIC
    outb(0x20, 0x20);
}



