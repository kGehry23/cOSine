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

#ifndef PAGER_H
#define PAGER_H

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>


/************************************
 * FUNCTION PROTOTYPES
 ************************************/

/*!
 * @brief Sets up and enables paging
 * @return None
 */
void init_paging(void);

/*!
 * @brief Sets the contents of the CR3 register
 * @return None
 */
void set_cr3(uint32_t* cr3_contents);

/*!
 * @brief Sets the contents of the CR0 register
 * @return None
 */
void set_cr0(uint32_t pg_set);

/*!
 * @brief Sets the contents of the CR4 register
 * @return None
 */
void set_cr4(uint32_t pae_set);

/*!
 * @brief Returns the contents of the CR3 register
 * @return None
 */
uint32_t* get_cr3();

void enable_paging(void);

void load_page_dir(uint32_t*);

#endif //PAGER_H


