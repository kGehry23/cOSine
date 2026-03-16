/**
 ********************************************************************************
 * @file    ata.c
 * 
 * @author  Kai Gehry
 * @date    2026-03-15
 *
 * @brief   ATA disk controller.
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "ata.h"

//Sets up the ATA drive for transfer 
void ata_init(void)
{
    identify_ata(DRIVE_SELECT_PRIMARY_ATA, SELECT_PRIMARY);
}

void identify_ata(uint16_t device_select_port, uint16_t device_select_byte)
{
    //Select the device
    outb(device_select_port, device_select_byte);

    //Set the sector cont, LBAlo, LBAmid, LBAhi ports to 0
    outb(SECTOR_COUNT, 0);
    outb(LBALO, 0);
    outb(LBAMID, 0);
    outb(LBAHI, 0);

    //Send the identify command and check the response
    outb(COMMAND_IO, IDENTIFY);
    uint8_t identify_byte = inb(COMMAND_IO);

    if(identify_byte != 0)
    {
        uint8_t status_port_data; 

        printf("Primary drive exists.\n");

        //Poll until the BSY bit 0
        status_port_data = (inb(COMMAND_IO)>>BSY_BIT)&0x1;
        while(status_port_data != 0)
        {
            status_port_data = (inb(COMMAND_IO)>>BSY_BIT)&0x1;
        }

        //Check if the LBAMID and LBAHI ports are 0 to determine if the drive is ATA
        if((inb(LBAMID) == 0) && inb(LBAHI) == 0)
            printf("The drive is ATA.\n");

        status_port_data = inb(COMMAND_IO);
        while((((status_port_data>>DRQ_BIT)&0x1) != 1) && (((status_port_data)&0x1) != 1))
        {
            status_port_data = inb(COMMAND_IO);
        }

        //Check to make sure the error bit (bit 0) of the status port is cleared
        if((status_port_data&0x1) == 0)
            printf("Ready to read/write data from the ATA device.\n\n");
    }

    else
        printf("Primary drive does not exist.\n\n");

}