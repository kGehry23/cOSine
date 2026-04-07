/**
 ********************************************************************************
 * @file    ps2.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-10
 *
 * @brief   Driver for the PS/2 controller. Definitions of functions to communicate 
 *          and test the PS/2 controller
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "ps2.h"
#include "../pit/pit.h"
#include "../../libc/stdio/stdio.h"

/*!
 * @brief Checks bit 0 of the PS/2 status register until set to 1
 * @return None
 */
void poll_status_bit_0(void)
{
    while(inb(PS2_READ_STATUS_PORT)&0x1 != 1);
}

/*!
 * @brief Checks bit 1 of the PS/2 status register until set to 0
 * @return None
 */
void poll_status_bit_1(void)
{
    while(((inb(PS2_READ_STATUS_PORT) >> 1)&0x1) != 0);
}

/*!
 * @brief Initializes and tests the PS/2 Controller
 * @return None
 */
void init_ps2_controller()
{
    disable_devices();
    set_config_byte();

    test_ps2_controller();
    test_dual_channel();
    test_ports();

    enable_devices();
    reset_devices();
}

/*!
 * @brief Disables both PS/2 Ports
 * @return None
 */
void disable_devices()
{
    outb(PS2_WRITE_COMMAND_PORT, DISABLE_PS2_PORT_1);
    outb(PS2_WRITE_COMMAND_PORT, DISABLE_PS2_PORT_2);
}

/*!
 * @brief Sets the configuration byte
 * @return None
 */
void set_config_byte()
{
    //Reads the config byte
    outb(PS2_WRITE_COMMAND_PORT, READ_CONTROLLER_CONFIG_BYTE);

    //Gets the config byte from the data port
    uint8_t config_byte = inb(PS2_READ_WRITE_DATA_PORT);

    //Modifies the config byte. Clears bits 0, 4, and 6
    config_byte &= 0xAE;

    //Writes the updated config byte to the data port
    outb(PS2_WRITE_COMMAND_PORT, WRITE_CONTROLLER_CONFIG_BYTE);
    outb(PS2_READ_WRITE_DATA_PORT, config_byte);
}

/*!
 * @brief Tests the PS/2 controller
 * @return Status code. 0x55 indicates the test has passed
 */
void test_ps2_controller()
{
    //Writes the test byte to the controller command port
    outb(PS2_WRITE_COMMAND_PORT, TEST_CONTROLLER);

    poll_status_bit_0();

    uint8_t test_byte = inb(PS2_READ_WRITE_DATA_PORT);
    printf("PS/2 self test: ");

    if(test_byte == SELF_TEST_PASSED)
        printf("%p -> Test Passed.\n", test_byte);
    else
        printf("%p -> Test Failed.\n", test_byte); 
        
}

/*!
 * @brief Tests if the PS/2 controller is dual channel
 * @return None
 */
void test_dual_channel()
{
    outb(PS2_WRITE_COMMAND_PORT, ENABLE_PS2_PORT_2);
    //Reads the config byte
    outb(PS2_WRITE_COMMAND_PORT, READ_CONTROLLER_CONFIG_BYTE);

    poll_status_bit_0();

    uint8_t config_byte = inb(PS2_READ_WRITE_DATA_PORT);

    printf("PS/2 dual channel test: ");

    //Check that bit 5 is cleared, confirming the controller is dual channel
    if(((config_byte >> 5) & 0x1) == 0)
        printf("Controller is dual channel\n");
    else
        printf("Controller is not dual channel\n");


    //Disable second channel ps2 port after test
    outb(PS2_WRITE_COMMAND_PORT, DISABLE_PS2_PORT_2);  

    //Modifies the config byte. Clears bits 1 and 5, disabling IRQs and enabling the clock for port 2
    config_byte &= 0xDD;
    //Writes the updated config byte to the data port
    outb(PS2_WRITE_COMMAND_PORT, WRITE_CONTROLLER_CONFIG_BYTE);
    outb(PS2_READ_WRITE_DATA_PORT, config_byte);
}

/*!
 * @brief Tests the PS/2 ports
 * @return None
 */
void test_ports(void)
{
    outb(PS2_WRITE_COMMAND_PORT, TEST_PORT_1);
    poll_status_bit_0();
    
    if(inb(PS2_READ_WRITE_DATA_PORT) == PORT_TEST_PASSED)
        printf("PS/2 Port 1 test passed\n");

    outb(PS2_WRITE_COMMAND_PORT, TEST_PORT_2);
    poll_status_bit_0();
    
    if(inb(PS2_READ_WRITE_DATA_PORT) == PORT_TEST_PASSED)
        printf("PS/2 Port 2 test passed\n");   
}

/*!
 * @brief Enables any PS/2 devices that exist and work
 * @return None
 */
void enable_devices()
{
    outb(PS2_WRITE_COMMAND_PORT, ENABLE_PS2_PORT_1);
    outb(PS2_WRITE_COMMAND_PORT, ENABLE_PS2_PORT_2);

    printf("PS/2 devices on ports 1 and 2 enabled\n");
    //Reads the config byte
    outb(PS2_WRITE_COMMAND_PORT, READ_CONTROLLER_CONFIG_BYTE);

    //Gets the config byte from the data port
    uint8_t config_byte = inb(PS2_READ_WRITE_DATA_PORT);

    //Modifies the config byte. Enables interrupts for port 1 and 2
    config_byte |= 0x3;
    config_byte &= 0xdf;

    //Writes the updated config byte to the data port
    outb(PS2_WRITE_COMMAND_PORT, WRITE_CONTROLLER_CONFIG_BYTE);
    outb(PS2_READ_WRITE_DATA_PORT, config_byte);

    printf("PS/2 interrupts for ports 1 and 2 enabled\n");
}

/*!
 * @brief Sends a byte to PS/2 port 1
 * @param data_byte Byte to send to the port 1 device
 * @return None
 */
void send_byte_port_1(uint8_t data_byte)
{
    poll_status_bit_1();
    outb(PS2_READ_WRITE_DATA_PORT, data_byte);
}

/*!
 * @brief Sends a byte to PS/2 port 2
 * @param data_byte Byte to send to the port 2 device
 * @return None
 */
void send_byte_port_2(uint8_t data_byte)
{
    //Set the port to be written to to port 2
    outb(PS2_WRITE_COMMAND_PORT, WRITE_PORT_2);

    poll_status_bit_1();
    outb(PS2_READ_WRITE_DATA_PORT, data_byte);
}

/*!
 * @brief Detects the device connected to a given PS/2 port
 * @param port Port to detect a device on
 * @return None
 */
static void detect_device(uint8_t port)
{
    //This uses polling... works for now, but need to properly set up interrupts

    if(port == 1)
        send_byte_port_1(0xF2);
    else if(port == 2)
        send_byte_port_2(0xF2);

    while(inb(PS2_READ_STATUS_PORT)&0x1 != 0)
    {
        printf("%p ", inb(PS2_READ_WRITE_DATA_PORT));
    }

    printf("\n");
}

/*!
 * @brief Reset devices connected to PS/2 ports
 * @return None
 */
void reset_devices()
{
    send_byte_port_1(RESET_DEVICES);
    send_byte_port_2(RESET_DEVICES);
}
