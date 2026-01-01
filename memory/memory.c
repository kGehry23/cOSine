/**
 ********************************************************************************
 * @file    memory.c
 * 
 * @author  Kai Gehry
 * @date    2025-12-31
 *
 * @brief   Defines standard dynamic memory functions for use by the kernel
 *     
 ********************************************************************************
 */

/************************************
* INCLUDES
************************************/
#include <stdint.h>
#include <stddef.h>

/************************************
 * DEFINES
 ************************************/
//Sample for now, does not need to be actual page size used
#define PAGE_SIZE 4096 //4KiB page size

extern uint32_t endkernel; //Address of end of kernel region
uint32_t *page_start_addr = (&endkernel) + 1; //4 bytes after the end of the kernel (next address)
uint32_t offset = 0;

/*!
 * @brief Allocates memory for the kernel. Very simplistic implementation here, far from complete
 * @param n Size in bytes of memory to allocate
 * @return Pointer to allocated memory
 */
void* k_malloc(size_t n)
{
    if(0==1)
    {
        //Need to find a condition here that would constitute not being able to allocate memory
        return 0;
    }
    else
    {
        //Calculates pointer to next available memory
        void* old_ptr = page_start_addr + offset;
        //Updates the offset for next allocation
        offset = offset + n/sizeof(void*);

        return old_ptr;
    }
}
