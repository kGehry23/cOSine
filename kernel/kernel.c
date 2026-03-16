/**
 ********************************************************************************
 * @file    kernel.c
 *
 * @date    2025-12-20
 *
 * @brief   Basic kernel code.
 * 
 *
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

//Drivers
#include "../drivers/ps2/ps2.h"
#include "../drivers/disk/ata.h"
#include "../drivers/ps2/keyboard/keyboard.h"
#include "../drivers/ps2/mouse/mouse.h"

#include "../memory/frame_allocator.h"
#include "../memory/paging/pager.h"
#include "../shell/shell.h"

//Address of end of kernel memory 
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

    //Initialize the ata drive
    ata_init();

    //Masks all interrupts except for the keyboard and mouse
    outb(PIC_MASTER_DATA,0xfd);

    /*1110 1111 -> irq 12 is the mouse*/ 
    outb(PIC_SLAVE_DATA,0xff);

    //Initializes the GDT
    init_GDT();
    printf("GDT initialization complete.\n\n");
    
    //Initializes IDT
    idt_init();
    printf("IDT initialization complete.\n\n");

    void (*handle)() = handle_key_press;
    set_irq_handler(handle,2);

    //For mouse when needed
    // handle = handle_mouse;
    // set_irq_handler(handle, 12);

    printf("Initializing PS/2 Controller...\n");
    init_ps2_controller();

    //Set interrupt flag (enables interrupts) 
    __asm__ volatile ("sti"); 

    // for(int i = 0; i < 1000000000;i++)
    // {
    //     //This is a horrible way to do this, however, this can be done for now
    // }

    //Initializes the shell
    // shell_init();

    for(;;) {
        asm("hlt");
    }
}

