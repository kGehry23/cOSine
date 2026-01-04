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
#include "memory.h"
#include "../libc/stdio/stdio.h"
#include "../data_structures/bitmap.h"

/************************************
 * DEFINES
 ************************************/
#define PAGE_SIZE 0x1000 //4KiB page size
#define PAGE_BATCH 20

//Macros used to define if a page is allocated or not
#define ALLOCATED 1     
#define UNALLOCATED 0

#define VOID_PTR_SIZE sizeof(void*)

typedef uint32_t* pageframe_t;

extern uint32_t endkernel; //Address of end of kernel region
uint32_t *page_start_addr = (&endkernel) + 1; //4 bytes after the end of the kernel (next address)
// uint32_t kernel_size = &endkernel - 0x00100000;

uint32_t max_pages = 1048319;

uint32_t offset = 0; //may not be needed

//Defines the frame table.... This needs to be changed to a byte array with the size of the number of total pages possible
bitmap_t frame_table;
pageframe_t pre_alloc_frames[PAGE_BATCH];

/*!
 * @brief Initializes the frame table
 * @return None
 */
void init_frametable()
{
    init_bitmap(&frame_table);
}

static pageframe_t k_get_frame()
{
    uint32_t i = 0;

    while(bit_state(&frame_table, i) != ALLOCATED)
    {
        i++;

        //catch case where there are no free frames
    }

    //Set the frame as allocated in the frame table
    set_bit_high(&frame_table, i);

    return page_start_addr + (i*PAGE_SIZE);
}

/*!
 * @brief Allocates a page frame. Will allocate a batch of frames if all pages in a 
 *        previously allocated batch have been used
 * @return Pointer to allocated page
 */
pageframe_t k_malloc_frame()
{
    static uint8_t allocate = 1;
    static uint8_t frame = 0;
    pageframe_t page;

    if(frame == PAGE_BATCH)
    {
        allocate = 1;
    }

    if(allocate == 1)
    {
        for(size_t i = 0; i < PAGE_BATCH; i++)
        {
            pre_alloc_frames[i] = k_get_frame();
        }
        allocate = 0;
        frame = 0;
    }

    page = pre_alloc_frames[frame];
    //Increment the number of allocated frames
    frame++;

    return page;
}


/*!
 * @brief Frees a page frame for use  
 * @return None
 */
void k_free_frame(pageframe_t p)
{
    uint32_t page_number = (*p-*page_start_addr)/PAGE_SIZE;
    set_bit_low(&frame_table, page_number);
}

/*!
 * @brief Allocates memory for the kernel. Very simplistic implementation here, far from complete
 * @param n Size in bytes of memory to allocate
 * @return Pointer to allocated memory
 */
void* k_malloc(size_t n)
{
    /*
        Note this does NOT consider fragmentation
    */

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
        unsigned int offset_addition = n/VOID_PTR_SIZE;
        
        //Ensures new allocations are aligned on a 4 byte boundary
        if(n%VOID_PTR_SIZE == 0)
            offset = offset + offset_addition;
        else
            offset = offset + offset_addition + 1;

        return old_ptr;
    }
}








