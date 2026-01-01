/**
 ********************************************************************************
 * @file    kernel.c
 *
 * @date    2025-12-20
 *
 * @brief   Basic kernel code.
 * 
 *          Credit: Adapted from https://wiki.osdev.org/Bare_Bones
 *      
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include <stdbool.h>
#include "terminal/terminal.h"
#include "../libc/stdio/stdio.h"
#include "../libc/stdlib/stdlib.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../data_structures/bitmap.h"

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    uint16_t *vga_ptr = (uint16_t*)0xB8000;

    terminal_initialize();
    printf("Booted into cOSine\nStarting address of VGA buffer: %p\n\n\n", vga_ptr);

    //Initializes the GDT
    init_GDT();
    printf("GDT initialization complete.\n\n");

    //Initializes IDT
    idt_init();
    printf("IDT initialization complete.\n\n");

    /*
        Once the PIC is initialized, interrupts can be enabled
    */

}







