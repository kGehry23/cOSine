/**
 ********************************************************************************
 * @file    frame_allocator.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-14
 *
 * @brief   Defines the page allocation mechanism
 * 
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "frame_allocator.h"
#include "../libc/stdio/stdio.h"


/************************************
 * GLOBAL AND STATIC VARIABLES
 ************************************/

//End of kernel memory
extern uint32_t endkernel;

//Base address of allocatable memory
static uint32_t* base_addr = &endkernel;

//Array to keep track of which pages are allocated and which are free
static uint8_t frame_array[MAX_PAGES];
static uint32_t* pre_alloced_frames[PAGE_BLOCK];


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

/*!
 * @brief Allocates frames when there are no more pages available
 *        from previous allocations
 * @return None
 */
uint32_t* allocate_frame()
{
    static unsigned int allocated = 0;

    //Once there are no more frames that are allocatable, allocate more
    if(allocated == PAGE_BLOCK)
    {
        allocated = 0;
        //Pre_allocate more frames
        pre_allocate_frames();
    }

    uint32_t *frame = pre_alloced_frames[allocated];
    allocated++;

    return frame;
}

/*!
 * @brief Frees a frame which has been allocated
 * @return None
 */
void free_frame(uint32_t* frame_address)
{
    //Rather than division by 4096 (expensive) use bit shift left by 12 (2^12 = 4096)
    uint32_t frame_number = (frame_address - base_addr)>>PAGE_SIZE_BASE_2;
    printf("Frame number: %d\n", frame_number);

    frame_array[frame_number] = FREE;
}

/*!
 * @brief Returns an available frame
 * @return None
 */
uint32_t* get_free_frame()
{
    static uint32_t i = 0;

    while(frame_array[i] != FREE)
    {
        //
        i++;
    }

    frame_array[i] = ALLOCATED;
    // i++;

    //Returns address of new page relative to base address
    return base_addr + (PAGE_SIZE*i);
}

/*!
 * @brief Pre-allocates a number of pages
 * @return None
 */
void pre_allocate_frames()
{
    for(size_t i = 0;i<PAGE_BLOCK;i++)
    {
        pre_alloced_frames[i] = get_free_frame();
    }
}

// void available_memory(void)
// {
//     printf("Available memory: %dM\n", (MAX_PAGES*PAGE_SIZE - (uint32_t)base_addr)/1000000);
// }