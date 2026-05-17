/**
 ********************************************************************************
 * @file    ps2.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-10
 *
 * @brief   Header for the PS/2 controller driver
 *     
 ********************************************************************************
 */

#ifndef PS2_H
#define PS2_H

/************************************
 * INCLUDES
 ************************************/
#include "io.h"
#include "pit.h"
#include "stdio.h"


/************************************
 * MACROS
 ************************************/
#define PS2_READ_WRITE_DATA_PORT        0x60
#define PS2_READ_STATUS_PORT            0x64
#define PS2_WRITE_COMMAND_PORT          0x64

#define WRITE_PORT_2                    0xD4

#define DISABLE_PS2_PORT_1              0xAD
#define DISABLE_PS2_PORT_2              0xA7

#define ENABLE_PS2_PORT_1               0xAE
#define ENABLE_PS2_PORT_2               0xA8

#define TEST_CONTROLLER                 0xAA
#define TEST_PORT_1                     0xAB
#define TEST_PORT_2                     0xA9

#define READ_CONTROLLER_CONFIG_BYTE     0x20
#define WRITE_CONTROLLER_CONFIG_BYTE    0x60

#define SELF_TEST_PASSED                0x55
#define PORT_TEST_PASSED                0x00

#define RESET_DEVICES                   0xFF


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Initializes and tests the PS/2 Controller
 * @return None
 */
void init_ps2_controller();

/*!
 * @brief Sets the configuration byte
 * @return None
 */
void set_config_byte(void);

/*!
 * @brief Sends a byte to PS/2 port 1
 * @param data_byte Byte to send to the port 2 device
 * @return None
 */
void send_byte_port_1(uint8_t data_byte);

/*!
 * @brief Sends a byte to PS/2 port 2
 * @param data_byte Byte to send to the port 2 device
 * @return None
 */
void send_byte_port_2(uint8_t data_byte);

#endif //PS2_H