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


/************************************
 * GLOBAL AND STATIC VARIABLES
 ************************************/
volatile uint32_t test_val = 0; //Declared volatile as modified from within ISR
static bool print_timer = false;


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Configures the PIT
void set_channel_mode(void)
{
    //0011 0110 -> Channel 0, lobyte/hibyte, square wave generator, binary mode
    outb(COMMAND_MODE_REG, 0x36);
}

//Reloads the PIT counter value
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

    return res;
}

//Enables character printing (for indication) when sleep is called
void enable_sleep_print(void)
{
    print_timer = true;
}

//Provides a delay for a specified number of miliseconds
void sleep(uint32_t miliseconds)
{
    test_val = 18.2065*((float)miliseconds/1000);

    while(test_val > 0)
    {

    }

    test_val = 0;
}

//IRQ0 handleer (PIT)
void timer_handler(void)
{    
    if(test_val > 0)
        test_val--;

    if(print_timer && test_val > 0)
        printf(".");

    //Send end of interrupt
    PIC_eoi(0);
}