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
char *key_codes[] = {
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "q","1","","","","z","s",
    "a","w","2","","","c","x",
    "d","e","4","3","",""," ",
    "v","f","t","r","5","","",
    "n","b","h","g","y","6","",
    "","","m","j","u","7","8",
    "","",",","k","i","o","0",
    "9","","",".","/","l",";",
    "p","-","","","","\"","",
    "[","=","","","","","\n",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","","",
    "","","","","","",""
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
            }
            else
                printf("%s", key_codes[reg_contents]);
        }
    }

    //Send EOI to PIC
    outb(0x20, 0x20);
}
