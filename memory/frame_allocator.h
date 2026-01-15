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

//Standard 4k page size
#define PAGE_SIZE   0x1000

//Number of frames to allocate at once
#define PAGE_BLOCK   20

#define MAX_PAGES    0x1000 //1M for now

#define ALLOCATED   0x01
#define FREE        0x00



/*!
 * @brief Allocates frames when there are no more pages available
 *        from previous allocations
 * @return None
 */
void allocate_frames(void);



