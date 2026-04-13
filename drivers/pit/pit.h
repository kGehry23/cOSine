/********************************************************************************
 * @file    pit.h
 * 
 * @author  Kai Gehry
 * @date    2026-04-04
 *
 * @brief   Header for the Programmable Interrupt Timer (PIT) driver.
 * 
 ********************************************************************************
*/

#ifndef PIT_H 
#define PIT_H

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>
#include <stdbool.h>
#include "../../libc/stdio/stdio.h"
#include "../../io/io.h"
#include "../pic/pic.h"


/************************************
 * MACROS
 ************************************/
#define CHANNEL_0_DATA      0x40
#define CHANNEL_1_DATA      0x41
#define CHANNEL_2_DATA      0x42
#define COMMAND_MODE_REG    0x43 


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Sets the PIT channel mode
 * @return None
 */
void set_channel_mode(void);

/*!
 * @brief Reloads the count value
 * @param count_val Count value
 * @return None
 */
void reload_count(uint16_t count_val);

/*!
 * @brief Reads the value of the count
 * @return 16 bit counter value
 */
uint16_t read_count_value(void);

/*!
 * @brief IRQ0 handler for timer interrupt
 * @return None
 */
void timer_handler(void);

/*!
 * @brief Enables printing a character to the screen when sleep is called
 * @return None
 */
void enable_sleep_print(void);

/*!
 * @brief Provides a delay given a number of milliseconds.
 * @param milliseconds Time to delay in miliseconds
 * @return None
 */
void sleep(uint32_t miliseconds);

#endif //PIT_H


