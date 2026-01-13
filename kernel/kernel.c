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
#include "tty/terminal.h"
#include "../libc/stdio/stdio.h"
#include "../libc/stdlib/stdlib.h"
#include "../gdt/gdt.h"
#include "../idt/idt.h"
#include "../pic/pic.h"
#include "../drivers/ps2/ps2.h"
// #include "data_structures/bitmap.h"

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    uint16_t *vga_ptr = (uint16_t*)0xB8000;

    terminal_initialize();
    printf("Booted into cOSine\nStarting address of VGA buffer: %p\n\n\n", vga_ptr);

    //Remap PIC
    PIC_remap();
    // printf("PIC remapped.\n\n");
    
    //Initializes the GDT
    init_GDT();
    // printf("GDT initialization complete.\n\n");
    
    //Initializes IDT
    idt_init();
    // printf("IDT initialization complete.\n\n");

    // printf("Initializing PS/2 Controller...\n");
    init_ps2_controller();

    for(;;) {
        asm("hlt");
    }
}







