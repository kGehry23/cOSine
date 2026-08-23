/**
 ********************************************************************************
 * @file   fat32.h
 * 
 * @author  Kai Gehry
 * @date    2026-03-16
 *
 * @brief   FATxx driver prototypes, typedefs, and related structures
 *     
 *          Reference: FAT Microsoft Documentation:
 *                     http://www.osdever.net/documents/fatgen103.pdf
 * 
 ********************************************************************************
 */

#ifndef FAT32_H
#define FAT32_H

/************************************
 * INCLUDES
************************************/
#include "stdint.h"
#include "../../../libc/stdio/stdio.h"


/************************************
 * TYPEDEFS
************************************/  
typedef struct 
{
    uint32_t disk_size;
    uint8_t sectors_per_cluster;
}disk_sec_to_cluster_t;


/************************************
 * GLOBAL VARIABLES
************************************/

uint32_t get_fat_size(void);
uint32_t get_first_data_sec_num(void);

#endif //FATXX_H

