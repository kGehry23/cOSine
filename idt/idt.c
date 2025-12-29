#include "idt.h"
#include <stdbool.h>

#define IDT_MAX_DESCRIPTORS 256

//Interrupt descriptor table. Contains 256 entries
__attribute__((aligned(0x10)))
static idt_entry_t idt[IDT_MAX_DESCRIPTORS];

//Interrupt descriptor table register
static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

/*!
 * @brief Generic exception handler
 */
void exception_handler()
{
    //Disables interrupts and halts the cpu
    __asm__ volatile ("cli; hlt");
}


void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_t* descriptor = &idt[vector];

    descriptor->offset_low = (uint32_t)isr & 0xFFFF;
    descriptor->segment_selector = 0x08; //Kernel code selector is located here in GDT
    descriptor->gate_attributes = flags;
    descriptor->offset_high = (uint32_t)isr >> 16;
    descriptor->reserved = 0;
}


void idt_init()
{
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for(uint8_t vector = 0;vector<32;vector++)
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); //Load idt
    __asm__ volatile ("sti"); //Set interrupt flag
}








