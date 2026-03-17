/**
 ********************************************************************************
 * @file   fat32.c
 * 
 * @author  Kai Gehry
 * @date    2026-03-16
 *
 * @brief   FATxx driver.
 *     
 *          Reference: FAT Microsoft Documentation:
 *                     http://www.osdever.net/documents/fatgen103.pdf
 * 
 ********************************************************************************
 */

/************************************
 * INCLUDES
************************************/
#include "fat32.h"

uint32_t BPB_RootEntCnt = 0; //Always 0 for FAT32
uint32_t RootDirSectors = 0; //Always 0 for fat 32 given BPB_RootEntCnt is 0
uint32_t BPB_RsvdSecCnt = 32;
uint32_t BPB_NumFATs = 2; //Provides redundancy for fat data structures

disk_sec_to_cluster_t disk_table_fat32[] = { 
        {66600, 0},
        {532480, 1},
        {16777216, 8},    
        {33554432, 16},
        {67108864, 32},
        {0xFFFFFFFF, 64}
};


uint32_t get_fat_size(void)
{
    disk_sec_to_cluster_t test = disk_table_fat32[4];

    uint32_t val1 = test.disk_size - (BPB_RsvdSecCnt+RootDirSectors);
    uint32_t val2 = (256*test.sectors_per_cluster) + BPB_NumFATs;

    val2 = val2/2;

    uint32_t fat_size = (val1+(val2-1))/val2;

    return fat_size;
}

uint32_t get_first_data_sec_num(void)
{
    return BPB_RsvdSecCnt + (BPB_NumFATs * get_fat_size()) + RootDirSectors;
}



