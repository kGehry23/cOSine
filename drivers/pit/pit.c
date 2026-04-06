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

//Configures the PIT
void set_channel_mode(void)
{
    //0000 0010 -> Channel 0, lobyte/hibyte, hardware-re-triggerable one shot, binary mode
    outb(COMMAND_MODE_REG, 0x36);
}


void reload_count(uint16_t count_val)
{
    __asm__ volatile("cli");

    outb(CHANNEL_0_DATA, 0);
    outb(CHANNEL_0_DATA, 0);
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