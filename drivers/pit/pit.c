/********************************************************************************
 * @file    pit.c
 * 
 * @author  Kai Gehry
 * @date    2026-04-04
 *
 * @brief  Programmable Interrupt Timer (PIT) driver
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "pit.h"

uint32_t test_val = 0;

//Configures the PIT
void set_channel_mode(void)
{
    //0011 0110 -> Channel 0, lobyte/hibyte, square wave generator, binary mode
    outb(COMMAND_MODE_REG, 0x36);
}


void reload_count(uint16_t count_val)
{
    outb(CHANNEL_0_DATA, count_val&0xFF);
    outb(CHANNEL_0_DATA, (count_val >> 8)&0xFF);
}

//Reads the PIT counter value
uint16_t read_count_value(void)
{
    //Disable interrupts
    __asm__ volatile("cli");

    outb(COMMAND_MODE_REG, 0x00);

    uint16_t res = inb(CHANNEL_0_DATA);
    res |= inb(CHANNEL_0_DATA) << 8;

    //Re-enable interrupts
    // __asm__ volatile("sti");

    return res;
}


void sleep(uint32_t miliseconds)
{
    test_val = 18.2065*((float)miliseconds/1000);

    while(test_val > 0)
    {

    }
}


void timer_handler(void)
{    
    if(test_val > 0)
        test_val--;

    //Send end of interrupt
    PIC_eoi(0);
}