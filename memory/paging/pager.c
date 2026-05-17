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
#include "frame_allocator.h"
#include "stdio.h"


/************************************
 * GLOBAL AND STATIC VARIABLES
 ************************************/

//Page directory. Aligned on 4kB boundary
uint32_t page_directory_1[1024] __attribute__((aligned(0x1000)));

//Initial page table. Aligned on 4kB boundary
uint32_t page_table_1 [1024] __attribute__((aligned(0x1000)));


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

/*!
 * @brief Initializes a page table
 * @return None
 */
void init_page_table(void)
{
    for(int i = 0;i<1024;i++)
    {
        /*Or'ing with 3 specifies that the entry maps to a 4 kB page
          and that the page can be read from and written to
        */

        page_table_1[i] = (i*PAGE_SIZE) | 3;
    }
}

/*!
 * @brief Initializes the page directory
 * @return None
 */
void init_page_directory(void)
{
    for(int i = 0;i<1024;i++)
    {
        //Sets a page as not present when set high
        page_directory_1[i] = 0x00000002;
    }

    //Initializes the page table and sets the initial entry in
    //the page directory to the address of the page table
    init_page_table();
    page_directory_1[0] = (uint32_t)page_table_1 | 3;
}


/*!
 * @brief Sets up and enables paging
 * @return None
 */
void init_paging(void)
{
    init_page_directory();

    //Sets CR3 to contain the address in bits 31-12 (4KB aligned)
    set_cr3(page_directory_1);
    //Enable 32-bit paging
    set_cr0(0x80000001);
}







