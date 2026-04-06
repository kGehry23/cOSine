/**
 ********************************************************************************
 * @file    frame_allocator.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-14
 *
 * @brief   Header for functions to allocate page frames.
 * 
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>
#include <stddef.h>

//Standard 4k page size
#define PAGE_SIZE   0x1000
#define PAGE_SIZE_BASE_2    12

//Number of frames to allocate at once
#define PAGE_BLOCK   1024

#define MAX_PAGES   0x1000

#define ALLOCATED   0x01
#define FREE        0x00


/*!
 * @brief Allocates frames when there are no more pages available
 *        from previous allocations
 * @return None
 */
uint32_t* allocate_frame(void);


void available_memory(void);

/*!
 * @brief Frees a frame which has been allocated
 * @return None
 */
void free_frame(uint32_t* frame_address);

/*!
 * @brief Returns an available frame
 * @return None
 */
uint32_t* get_free_frame(void);

/*!
 * @brief Pre-allocates a number of pages
 * @return None
 */
void pre_allocate_frames(void);
