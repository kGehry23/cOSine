/**
 ********************************************************************************
 * @file    ata.h
 * 
 * @author  Kai Gehry
 * @date    2026-03-15
 *
 * @brief   ATA disk controller prototypes and macros.
 *     
 ********************************************************************************
 */

#ifndef ATA_H
#define ATA_H

/************************************
 * INCLUDES
 ************************************/
#include "../../../libc/stdio/stdio.h"
#include "../../../io/io.h"

/************************************
 * DEFINES
 ************************************/

//Ports
#define DRIVE_SELECT_PRIMARY_ATA    0x1F6
#define COMMAND_IO                  0x1F7
#define SECTOR_COUNT                0x1F2
#define LBALO                       0x1F3
#define LBAMID                      0x1F4
#define LBAHI                       0x1F5
#define SECTOR_DATA_PORT            0x1F0

//Command bytes
#define SELECT_PRIMARY              0xA0
#define IDENTIFY                    0xEC
#define CACHE_FLUSH                 0xE7
#define READ_SECTORS                0x20
#define WRITE_SECTORS               0x30

//Status port bits
#define DRQ_BIT                     3
#define BSY_BIT                     7


/*!
 * @brief Initializes an ATA drive
 * @return None
 */
void ata_init(void);

/*!
 * @brief Sends the IDENTIFY sequence to a selected ata device
 * @param device_select_port Port for device selection (primary/secondary drive)
 * @param device_select_byte Command byte to select the master or slave drive
 * @return None
 */
void identify_ata(uint16_t device_select_port, uint16_t device_select_byte);

/*!
 * @brief Flushes the ATA cache
 * @return None
 */
void flush_cache(void);

/*!
 * @brief Reads a sector from disk.
 * @return None
 */
void read_sector(uint32_t lba);

/*!
 * @brief Writes a sector to disk.
 * @return None
 */
void write_sector(uint32_t lba);


#endif //ATA_H
