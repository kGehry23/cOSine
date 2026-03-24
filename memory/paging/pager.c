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

//Page directory. Aligned on 4kB boundary
uint32_t page_directory[1024] __attribute__((aligned(0x1000)));

//Initial page table. Aligned on 4kB boundary
uint32_t page_table [1024] __attribute__((aligned(0x1000)));

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
        page_table[i] = (i*PAGE_SIZE) | 3;
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
        page_directory[i] = 0x00000002;
    }

    //Initializes the page table and sets the initial entry in
    //the page directory to the address of the page table
    init_page_table();
    page_directory[0] = (uint32_t)page_table | 3;
}


/*!
 * @brief Sets up and enables paging
 * @return None
 */
void init_paging()
{
    init_page_directory();

    //Sets CR3 to contain the address in bits 31-12 (4KB aligned)
    set_cr3((uint32_t)page_directory);
    //Enable 32-bit paging
    set_cr0(0x80000000);
}

static uint32_t get_pte(uint32_t pde, uint32_t linear_address)
{
    /*Extracts bits 21-12 of the linear address address shifted down to
      positions 11-2. This is or'd with bits 31-12 of the linear pde to 
      extract the address of the correct page table entry
    */

    return pde | ((linear_address >> 10) & 0xFFA);
}

uint32_t get_physical_addr(uint32_t pte, uint32_t linear_address)
{
    /*Retains bits 11-0 from the original linear address, to offset into 
      the page table endtry provided
    */
    return pte | (linear_address & 0xFFF);
}





