/**
 ********************************************************************************
 * @file    gdt.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-28
 *
 * @brief   Global descriptor table function prototypes.
 *     
 ********************************************************************************
 */

#ifndef GDT_H
#define GDT_H

/*!
 * @brief Tells the CPU where to find the GDT
 * @param base Starting address of the GDT
 * @param limit Size of the GDT
 * @return None
 */
void setGDT(unsigned int limit, unsigned int base);

/*!
 * @brief Reloads the code and data segment registers
 * @return None
 */
void reloadSegments(void);

/*!
 * @brief Performs initialization of the GDT
 * @return None
 */
void init_GDT(void);

#endif //GDT_H 