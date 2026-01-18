#include "pager.h"
#include <stddef.h>
#include "../../libc/stdio/stdio.h"

//Page directory. Aligned on 4kB boundary
uint32_t page_directory[1024] __attribute__((aligned(0x1000)));

uint32_t page_table [1024] __attribute__((aligned(0x1000)));

static void init_page_directory()
{
    for(size_t i = 0;i<1024;i++)
    {
        //Sets a page as not present when set high
        page_directory[i] = 0x00000002;
    }
}

void init_paging()
{
    init_page_directory();
    //Sets CR3 to contain the address in bits 31-12 (4KB aligned)
    set_cr3(page_directory);

    //Enable 32-bit paging
    set_cr0(0x80000000);
    set_cr4(0x0);
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





