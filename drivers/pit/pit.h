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
#include "../../io/io.h"


/************************************
 * DEFINES
 ************************************/
#define CHANNEL_0_DATA      0x40
#define CHANNEL_1_DATA      0x41
#define CHANNEL_2_DATA      0x42
#define COMMAND_MODE_REG    0x43


/*!
 * @brief Sets the PIT channel mode
 * @return None
 */
void set_channel_mode(void);

void reload_count(uint16_t count_val);

uint16_t read_count_value(void);


#endif //PIT_H


