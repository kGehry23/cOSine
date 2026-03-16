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
 * DEFINES
 ************************************/
#define DRIVE_SELECT_PRIMARY_ATA    0x01F6
#define COMMAND_IO                  0x1F7

#define SELECT_PRIMARY              0xA0
#define IDENTIFY                    0xEC

#define SECTOR_COUNT                0x1F2
#define LBALO                       0x1F3
#define LBAMID                      0x1F4
#define LBAHI                       0x1F5

#define ERR_BIT                     0
#define DRQ_BIT                     3
#define BSY_BIT                     7

/************************************
 * INCLUDES
 ************************************/
#include "../../libc/stdio/stdio.h"
#include "../../io/io.h"

/*!
 * @brief Initializes an ATA drive
 * @return None
 */
void ata_init(void);

/*!
 * @brief Initializes an ATA drive
 * @param device_select_port Port for device selection (primary/secondary drive)
 * @return None
 */
void identify_ata(uint16_t device_select_port, uint16_t device_select_byte);

#endif //ATA_H
