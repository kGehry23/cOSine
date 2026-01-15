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

//End of kernel memory
extern uint32_t endkernel;

//Base address of allocatable memory
uint32_t *base_addr = &endkernel;

/*!
 * @brief Allocates frames when there are no more pages available
 *        from previous allocations
 * @return None
 */
void allocate_frames(void)
{
    


}

/*!
 * @brief Returns an available frame
 * @return None
 */
uint32_t* get_frame(void)
{
    static unsigned int allocated = 0;

    //Once there are no more frames that are allocatable, allocate more
    if(allocated == PAGE_BLOCK)
    {
        allocated = 0;
        //Allocate more frames
        allocate_frames();
        base_addr += (PAGE_BLOCK*PAGE_SIZE);
    }

    /*Calculate the starting address of the allocated memory to return.
      
      allocated = base + 4096(bytes) * num allocated pages + 1 (prevents overlap)
    */
    uint32_t* allocated_address = base_addr + PAGE_SIZE*allocated + 1;

    allocated++;

    return allocated_address;
}
