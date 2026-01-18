/********************************************************************************
 * @file    pager.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-17
 *
 * @brief   Header for 32 bit paging related functions and setup.
 * 
 ********************************************************************************
*/

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>

void init_paging(void);

void set_cr3(uint32_t* cr3_contents);

void set_cr0(uint32_t pg_set);

void set_cr4(uint32_t pae_set);

uint32_t* get_cr3();


