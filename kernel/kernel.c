/**
 ********************************************************************************
 * @file    kernel.c
 *
 * @date    2025-12-20
 *
 * @brief   Basic kernel code.
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


//Drivers
#include "../drivers/ps2/ps2.h"
#include "../drivers/disk/ATA/ata.h"
#include "../drivers/ps2/keyboard/keyboard.h"
// #include "../drivers/ps2/mouse/mouse.h"
#include "../drivers/pit/pit.h"
#include "../drivers/pic/pic.h"

#include "../memory/frame_allocator.h"
#include "../memory/paging/pager.h"
#include "../shell/shell.h"

#include "../task/task.h"


/************************************
 * STATIC AND GLOBAL VARIABLES
 ************************************/
task main_task;


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

/*!
 * @brief Kernel
 * @return None
 */
void kernel(void)
{

    //Creates a page directory, initial page table, and enables paging
    pre_allocate_frames();
    init_paging();

    //Initialize terminal
    terminal_initialize();
    printf("******** Booted into cOSine ********\n\n");

    //Remap PIC
    PIC_remap();
    printf("PIC remapped.\n\n");

    //Masks all interrupts except pit
    outb(PIC_MASTER_DATA,0xfe);
    
    /*1110 1111 -> irq 12 is the mouse*/ 
    outb(PIC_SLAVE_DATA,0xff);
    
    //Initializes the GDT
    init_GDT();
    printf("GDT initialization complete.\n\n");
    
    //Initializes IDT
    idt_init();
    printf("IDT initialization complete.\n\n");

    //Setup IRQ0 and initialize PIT
    void (*pit_handle)() = timer_handler;
    set_irq_handler(pit_handle,1);

    set_channel_mode();
    reload_count(0);

    //Setup IRQ1 and initialize keyboard
    void (*keyboard_handle)() = handle_key_press;
    set_irq_handler(keyboard_handle,2);

    //Set interrupt flag (enables interrupts) 
    __asm__ volatile ("sti");

    //PS/2 initialization 
    printf("Initializing PS/2 Controller...\n");
    init_ps2_controller();

    //Select and initialize ATA drive
    ata_init();

    //Sleep for 2 seconds before starting shell
    sleep(2000);

    //Unmask keyboard interrupt
    outb(PIC_MASTER_DATA,0xfc);

    shell_init();

    for(;;) {
        asm("hlt");
    }
}

