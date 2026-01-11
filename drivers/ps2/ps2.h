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

/************************************
 * INCLUDES
 ************************************/
#include "../../io/io.h"

/************************************
 * DEFINES
 ************************************/
#define PS2_READ_WRITE_DATA_PORT 0x60
#define PS2_READ_STATUS_PORT 0x64
#define PS2_WRITE_COMMAND_PORT 0x64

#define WRITE_PORT_2 0xD4

#define DISABLE_PS2_PORT_1 0xAD
#define DISABLE_PS2_PORT_2 0xA7

#define ENABLE_PS2_PORT_1 0xAE
#define ENABLE_PS2_PORT_2 0xA8

#define TEST_CONTROLLER 0xAA
#define TEST_PORT_1 0xAB
#define TEST_PORT_2 0xA9

#define READ_CONTROLLER_CONFIG_BYTE 0x20
#define WRITE_CONTROLLER_CONFIG_BYTE 0x60

#define SELF_TEST_PASSED 0x55
#define PORT_TEST_PASSED 0x00

#define RESET_DEVICES 0xFF


#ifndef PS2_KEYBOARD_H
#define PS2_KEYBOARD_H

/*!
 * @brief Checks bit 0 of the PS/2 status register until set to 1
 * @return None
 */
void poll_status_port(void);

/*!
 * @brief Initializes and tests the PS/2 Controller
 * @return None
 */
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

/*!
 * @brief Tests if the PS/2 controller is dual channel
 * @return None
 */
void test_dual_channel(void);

/*!
 * @brief Tests the PS/2 ports
 * @return None
 */
void test_ports(void);

/*!
 * @brief Enables any PS/2 devices that exist and work
 * @return None
 */
void enable_devices(void);

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

/*!
 * @brief Reset devices connected to PS/2 ports
 * @return None
 */
void reset_devices(void);

void check_input(void);


#endif //PS2_KEYBOARD_H