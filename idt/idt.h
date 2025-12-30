/**
 ********************************************************************************
 * @file    idt.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-29
 *
 * @brief   Interrupt descriptor table structures and
 *          operations
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdint.h>

#ifndef IDT_H
#define IDT_H

/*
    Struct representing a gate descriptor
*/
typedef struct
{
    uint16_t offset_low;
    uint16_t segment_selector;
    uint8_t reserved;
    uint8_t gate_attributes;
    uint16_t offset_high;
}__attribute__((packed)) idt_entry_t;

/*
    Struct representing the interrupt descriptor table register
*/
typedef struct
{
    uint16_t limit;
    uint32_t base;  
}__attribute__((packed)) idtr_t;


/*!
 * @brief Generic exception handler
 */
void exception_handler(void);

/*!
 * @brief Initializes an IDT gate
 * @param vector Vector number to assign to a given gate
 * @param isr Interrupt service routine to assign to a gate
 * @param flags Hex number which defines the attributes section of a gate 
 * @return None
 */
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

/*!
 * @brief Initializes the IDT
 * @return None
 */
void idt_init(void);

void setIDT(unsigned int limit, unsigned int base);

#endif //IDT_H

