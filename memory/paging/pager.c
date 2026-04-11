/********************************************************************************
 * @file    pager.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-17
 *
 * @brief   Defines functions for 32 bit paging.
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include "pager.h"
#include <stddef.h>
#include "../frame_allocator.h"
#include "../../libc/stdio/stdio.h"


/************************************
 * GLOBAL AND STATIC VARIABLES
 ************************************/

//Page directory. Aligned on 4kB boundary
uint32_t page_directory_1[1024] __attribute__((aligned(0x1000)));
uint32_t page_directory_2[1024] __attribute__((aligned(0x1000)));

//Initial page table. Aligned on 4kB boundary
uint32_t page_table_1 [1024] __attribute__((aligned(0x1000)));
uint32_t page_table_2 [1024] __attribute__((aligned(0x1000)));
// uint32_t page_table_3 [1024] __attribute__((aligned(0x1000)));
// uint32_t page_table_4 [1024] __attribute__((aligned(0x1000)));


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

/*!
 * @brief Initializes a page table
 * @return None
 */
void init_page_table()
{
    for(int i = 0;i<1024;i++)
    {
        /*Or'ing with 3 specifies that the entry maps to a 4 kB page
          and that the page can be read from and written to
        */
        page_table_1[i] = (i*PAGE_SIZE) | 3;
        page_table_2[i] = (i*PAGE_SIZE) | 3;
        // page_table_3[i] = (i*PAGE_SIZE) | 3;
        // page_table_4[i] = (i*PAGE_SIZE) | 3;
    }
}

/*!
 * @brief Initializes the page directory
 * @return None
 */
void init_page_directory()
{
    for(int i = 0;i<1024;i++)
    {
        //Sets a page as not present when set high
        page_directory_1[i] = 0x00000002;
        page_directory_2[i] = 0x00000002;
    }

    //Initializes the page table and sets the initial entry in
    //the page directory to the address of the page table
    init_page_table();
    page_directory_1[0] = (uint32_t)page_table_1 | 3;
    page_directory_2[0] = (uint32_t)page_table_2 | 3;
    // page_directory[1] = (uint32_t)page_table_2 | 3;
    // page_directory[2] = (uint32_t)page_table_3 | 3;
    // page_directory[3] = (uint32_t)page_table_4 | 3;
}

uint32_t alloc_page(void)
{
    static uint32_t i = 0;
    uint32_t page;

    switch (i)
    {
        case 0:
            page = page_table_1[0];
            break;
        case 1:
            page = page_table_2[0];
            break;
        // case 2:
        //     page = page_table_3[0];
        //     break;
        // case 3:
        //     page = page_table_4[0];
        //     break;
    }

    i++;

    return page;
}


/*!
 * @brief Sets up and enables paging
 * @return None
 */
void init_paging()
{
    init_page_directory();

    //Sets CR3 to contain the address in bits 31-12 (4KB aligned)
    set_cr3(page_directory_1);
    //Enable 32-bit paging
    set_cr0(0x80000000);
}







