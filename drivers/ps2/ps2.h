#include "../../io/io.h"
#include <stdint.h>

#define PS2_READ_WRITE_DATA_PORT 0x60
#define PS2_READ_STATUS_PORT 0x64
#define PS2_WRITE_COMMAND_PORT 0x64

#define DISABLE_PS2_PORT_1 0xAD
#define DISABLE_PS2_PORT_2 0xA7

#define TEST_CONTROLLER_BYTE 0xAA
#define READ_CONTROLLER_CONFIG_BYTE 0x20
#define WRITE_CONTROLLER_CONFIG_BYTE 0x60


#ifndef PS2_KEYBOARD_H
#define PS2_KEYBOARD_H


void init_ps2_controller();

/*!
 * @brief Disables both PS/2 Ports
 * @return None
 */
void disable_devices(void);

/*!
 * @brief Sets the configuration byte
 * @return None
 */
void set_config_byte(void);

/*!
 * @brief Tests the PS/2 controller
 * @return None
 */
void test_ps2_controller(void);

#endif //PS2_KEYBOARD_H