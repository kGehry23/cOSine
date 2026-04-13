/**
 ********************************************************************************
 * @file    ata.c
 * 
 * @author  Kai Gehry
 * @date    2026-03-15
 *
 * @brief   ATA disk driver. Uses PIO with 28 bit addressing.
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "ata.h"


/************************************
 * FUNCTION PROTOTYPES
 ************************************/
static void flush_cache(void);
static void delay_400ns(void);
static void poll_status_port(void);
static void identify_ata(uint16_t device_select_port, uint16_t device_select_byte);


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Sets up the ATA drive for transfer 
void ata_init(void)
{
    identify_ata(DRIVE_SELECT_PRIMARY, SELECT_PRIMARY);
}

//Reads the contents of a disk sector
void read_sector(uint32_t lba, uint16_t* data_array)
{
    outb(DRIVE_SELECT_PRIMARY, MASTER | ((lba >> 24)&0x0F));
    outb(FEATURES, NULL_BYTE);
    outb(SECTOR_COUNT, SEC_COUNT_256);
    outb(LBALO, (unsigned char)lba);
    outb(LBAMID, ((unsigned char)lba>>8));
    outb(LBAHI, ((unsigned char)lba>>16));

    outb(COMMAND_IO, READ_SECTORS);

    poll_status_port();

    for(int i = 0; i < SECTOR_WORDS; i++)
        data_array[i] = inw(SECTOR_DATA_PORT);
}

//Writes to a disk sector
void write_sector(uint32_t lba, uint16_t* data_array)
{
    outb(DRIVE_SELECT_PRIMARY, MASTER | ((lba >> 24)&0x0F));
    outb(FEATURES, NULL_BYTE);
    outb(SECTOR_COUNT, SEC_COUNT_256);
    outb(LBALO, (unsigned char)lba);
    outb(LBAMID, ((unsigned char)lba>>8));
    outb(LBAHI, ((unsigned char)lba>>16));

    outb(COMMAND_IO, WRITE_SECTORS);

    poll_status_port();

    for(int i = 0; i < SECTOR_WORDS; i++)
    {
        outw(SECTOR_DATA_PORT, data_array[i]);
        flush_cache();
    }
}

/*!
 * @brief Flushes the ATA cache
 * @return None
 */
static void flush_cache(void)
{
    outb(COMMAND_IO, CACHE_FLUSH);
}

/*!
 * @brief Polls the status port
 * @return None
 */
static void poll_status_port(void)
{
    uint8_t status_port_data;

    //Checks the state of the busy bit in the status byte
    status_port_data = inb(COMMAND_IO);
    while(((status_port_data >> BSY_BIT)&0x01 != 0))
        status_port_data = inb(COMMAND_IO);

    //Checks the state of the drq bit in the status byte
    status_port_data = inb(COMMAND_IO);
    while(((status_port_data >> DRQ_BIT)&0x01 != 1))
        status_port_data = inb(COMMAND_IO);
}

/*!
 * @brief Provides a 400 nano second delay
 * @return None
 */
static void delay_400ns(void)
{
    inb(COMMAND_IO);
    inb(COMMAND_IO);
    inb(COMMAND_IO);
    inb(COMMAND_IO);
}

/*!
 * @brief Sends the identify comand to an attached device. Provides device 
 *        identification and discovery.
 * @param device_select_port    Master or slave drive port
 * @param device_select_byte    Command byte for master or slave device
 * @return None
 */
static void identify_ata(uint16_t device_select_port, uint16_t device_select_byte)
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
            status_port_data = (inb(COMMAND_IO)>>BSY_BIT)&0x1;

        //Check if the LBAMID and LBAHI ports are 0 to determine if the drive is ATA
        if((inb(LBAMID) == 0) && inb(LBAHI) == 0)
            printf("The drive is ATA.\n");

        poll_status_port();

        //Check to make sure the error bit (bit 0) of the status port is cleared
        if((status_port_data&0x1) == 0)
            printf("Ready to read/write data from the ATA device.\n\n");

        //Clears garbage data in disk cache from call to identify
        for(int i = 0; i < SECTOR_WORDS; i++)
            inw(SECTOR_DATA_PORT);
    }

    else
        printf("Primary drive does not exist.\n\n");
}

