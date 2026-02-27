/********************************************************************************
 * @file    mouse.c
 * 
 * @author  Kai Gehry
 * @date    2026-02-26
 *
 * @brief   Mouse driver 
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "mouse.h"

void handle_mouse(void)
{
    // send_byte_port_2(ENABLE_DATA_REPORTING);
    printf("Byte read back from port 2: %p\n", inb(0x60));
}