/**
 ********************************************************************************
 * @file    idt.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-29
 *
 * @brief   Definition of the interrupt descriptor table structures and
 *          operations
 *     
 ********************************************************************************
 */

/************************************
 * DEFINES
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

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

void idt_init(void);

#endif //IDT_H

