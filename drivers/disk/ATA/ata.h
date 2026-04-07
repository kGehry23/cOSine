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
#include "../../pit/pit.h"


/************************************
 * MACROS
 ************************************/

//Ports
#define DRIVE_SELECT_PRIMARY        0x1F6
#define COMMAND_IO                  0x1F7
#define SECTOR_COUNT                0x1F2
#define FEATURES                    0x1F1
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

//Number of 16 bit entries in a sector (total 512 bytes)
#define SIXTEEN_BIT_ELEMENTS        256


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Initializes an ATA drive
 * @return None
 */
void ata_init(void);

/*!
 * @brief Reads a sector from disk.
 * @return None
 */
void read_sector(uint32_t lba, uint16_t* data_array);

/*!
 * @brief Writes a sector to disk.
 * @return None
 */
void write_sector(uint32_t lba, uint16_t* data_array);


#endif //ATA_H
