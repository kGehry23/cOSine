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

//Disk data array
uint16_t arr[256];

//Sets up the ATA drive for transfer 
void ata_init(void)
{
    identify_ata(DRIVE_SELECT_PRIMARY_ATA, SELECT_PRIMARY);
}

//Flushes the ATA cache
void flush_cache(void)
{
    outb(COMMAND_IO, CACHE_FLUSH);
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

        //Poll until the BSY bit is 0
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

void read_sector(uint32_t lba)
{
    uint8_t status_port_data;

    outb(DRIVE_SELECT_PRIMARY_ATA, 0xE0 | ((lba >> 24) & 0x0F));
    outb(SECTOR_COUNT, 0);
    outb(LBALO, lba&0xFF);
    outb(LBAMID, (lba>>8)&0xFF);
    outb(LBAHI, (lba>>16)&0xFF);

    outb(COMMAND_IO, READ_SECTORS);

    status_port_data = inb(COMMAND_IO);
    while((((status_port_data>>DRQ_BIT)&0x1) != 1) && (((inb(COMMAND_IO)>>BSY_BIT)&0x1) != 0))
    {
        status_port_data = inb(COMMAND_IO);
    }

    for(int i = 0; i < 256; i++)
        arr[i] = inb(SECTOR_DATA_PORT);

    for(int i = 0; i < 256; i++)
        printf("%d ", arr[i]);

    printf("\n");

    for(int i = 0; i < 10000000; i++)
        continue;
}

void write_sector(uint32_t lba)
{
    uint8_t status_port_data;

    outb(DRIVE_SELECT_PRIMARY_ATA, 0xE0 | ((lba >> 24) & 0x0F));
    outb(SECTOR_COUNT, 0);
    outb(LBALO, lba);
    outb(LBAMID, (lba>>8));
    outb(LBAHI, (lba>>16));

    outb(COMMAND_IO, WRITE_SECTORS);

    status_port_data = inb(COMMAND_IO);
    while((((status_port_data>>DRQ_BIT)&0x1) != 1) && (((inb(COMMAND_IO)>>BSY_BIT)&0x1) != 0))
    {
        status_port_data = inb(COMMAND_IO);
    }

    for(int i = 0; i < 256; i++)
    {
        uint16_t val = 12;
        outb(SECTOR_DATA_PORT, val&0xFF);
        outb(SECTOR_DATA_PORT, (val>>8)&0xFF);

        for(int j = 0; j < 1000000; j++)
            continue;

        flush_cache();
    }

    printf("\n");
}

