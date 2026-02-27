/********************************************************************************
 * @file    mouse.h
 * 
 * @author  Kai Gehry
 * @date    2026-02-26
 *
 * @brief   Mouse driver 
 * 
 ********************************************************************************
*/

/************************************
 * DEFINE
 ************************************/
#define DATA_PORT   0x60
#define STATUS_PORT 0x64

#define ENABLE_DATA_REPORTING 0xF4

/************************************
 * INCLUDES
 ************************************/
#include <stdbool.h>
#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"
#include "../../../idt/idt.h"
#include "../../../pic/pic.h"
#include "../ps2.h"

/*!
 * @brief IRQ handler for IRQ12
 * @return None
 */
void handle_mouse(void);

