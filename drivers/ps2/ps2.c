#include "ps2.h"
#include "../../libc/stdio/stdio.h"

/*!
 * @brief Initializes the PS/2 Controller
 * @return None
 */
void init_ps2_controller()
{
    disable_devices();
    set_config_byte();
    test_ps2_controller();
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
    config_byte = config_byte & 0xAE;

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
    outb(PS2_WRITE_COMMAND_PORT, TEST_CONTROLLER_BYTE);

    //Continue to check the port while bit 0 in the status register is not set
    while(inb(PS2_READ_STATUS_PORT)&0x1 != 1);

    uint8_t test_byte = inb(PS2_READ_WRITE_DATA_PORT);
    printf("Test Result: ");

    if(test_byte == 0x55)
        printf("%p -> Test Passed.\n", test_byte);
    else
        printf("%p -> Test Failed.\n", test_byte);    
}
