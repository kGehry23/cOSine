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
#include "../pic/pic.h"

//Drivers
#include "../drivers/ps2/ps2.h"
#include "../drivers/disk/ATA/ata.h"
#include "../drivers/disk/FAT/fat32.h"
#include "../drivers/ps2/keyboard/keyboard.h"
#include "../drivers/ps2/mouse/mouse.h"

#include "../memory/frame_allocator.h"
#include "../memory/paging/pager.h"
#include "../shell/shell.h"

#include "../task/task.h"

//Address of end of kernel memory 
extern uint32_t endkernel;

void test1(void)
{
    printf("Test 1 ");
}
void test2(void)
{
    printf("Test 2 ");
}

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

    // printf("FAT Size: %d\n", get_fat_size());
    // printf("First data sector number: %d\n\n", get_first_data_sec_num());

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

    task main_task;
    task shell;
    // create_new_task(&main_task, test1, 0, get_cr3());
    create_new_task(&shell, shell_init, 0, get_cr3());
    switch_state(&main_task.registers, &shell.registers); 

    // for(;;) {
    //     asm("hlt");
    // }
}

