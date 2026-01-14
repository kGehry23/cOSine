/**
 ********************************************************************************
 * @file    idt.c
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
 * INCLUDES
 ************************************/
#include "idt.h"
#include <stdbool.h>
#include "../libc/stdio/stdio.h"
#include "../pic/pic.h"

/************************************
 * DEFINES
 ************************************/
#define IDT_MAX_DESCRIPTORS 256

//Interrupt descriptor table. Contains 256 entries
__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

//Interrupt descriptor table register
static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS];

//isr stub table defined in idt.asm
extern void* isr_stub_table[];
void *irq_functions[16];

/*!
 * @brief Generic exception handler
 * @return None
 */
void exception_handler()
{
    //Disables interrupts and halts the cpu
    printf("Test\n");
    __asm__ volatile ("cli; hlt");
}

/*!
 * @brief General interrupt handler
 * @return None
 */
void interrupt_handler()
{
    void (*handle)();

    handle = irq_functions[2];

    handle();
}

void set_irq_handler(void (*handler)(), uint8_t irq_number)
{
    irq_functions[irq_number] = handler;
}

/*!
 * @brief Initializes an IDT gate
 * @param vector Vector number to assign to a given gate
 * @param isr Interrupt service routine to assign to a gate
 * @param flags Hex number which defines the attributes section of a gate 
 * @return None
 */
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_t* descriptor = &idt[vector];

    descriptor->offset_low = (uint32_t)isr & 0xFFFF;
    descriptor->segment_selector = 0x08; //Kernel code selector is located here in GDT
    descriptor->gate_attributes = flags;
    descriptor->offset_high = (uint32_t)isr >> 16;
    descriptor->reserved = 0;
}

/*!
 * @brief Initializes the IDT
 * @return None
 */
void idt_init()
{
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    printf("Limit of idt entries: %d\n", idtr.limit);
    printf("IDT loaded at address %p\n", idtr.base);

    for(uint8_t vector = 0;vector<48;vector++)
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }


    //Sets the IDT. Called from asm file instead of inline asm. Issues with base address otherwise 
    setIDT(idtr.limit, idtr.base);

    // __asm__ volatile ("lidt %0" : : "m"(idtr)); //Load idt

    __asm__ volatile ("sti"); //Set interrupt flag (enables interrupts) 
}








