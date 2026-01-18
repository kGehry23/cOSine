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
#include "../drivers/ps2/keyboard/keyboard.h"
#include "../memory/frame_allocator.h"
#include "../memory/paging/pager.h"
#include "../shell/shell.h"
// #include "data_structures/bitmap.h"

extern uint32_t endkernel;

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{
    //Creates a page directory, initial page table, and enables paging
    init_paging();

    terminal_initialize();
    printf("Booted into cOSine\n");

    //Remap PIC
    PIC_remap();
    printf("PIC remapped.\n\n");

    //Masks all interrupts except for the keyboard
    outb(PIC_MASTER_DATA,0xfd);
    outb(PIC_SLAVE_DATA,0xff);

    //Initializes the GDT
    init_GDT();
    printf("GDT initialization complete.\n\n");
    
    //Initializes IDT
    idt_init();
    printf("IDT initialization complete.\n\n");

    void (*handle)() = handle_key_press;
    set_irq_handler(handle,2);

    printf("Initializing PS/2 Controller...\n");
    init_ps2_controller();

    //Set interrupt flag (enables interrupts) 
    __asm__ volatile ("sti"); 
    inb(0x60);//Make sure that that the 

    shell_init();
    //Clears the terminal 
    // terminal_initialize();
    // printf("cOSine:$ "); //Prints the shell text... does noting currently
    

    for(;;) {
        asm("hlt");
    }
}

