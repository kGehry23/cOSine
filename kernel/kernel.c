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

    //End address of the kernel defined in linker script
    extern uint32_t endkernel;

    printf("End kernel address: %p\n\n", &endkernel);

    int* ptr = (int*)k_malloc(sizeof(int));
    printf("Address of allocated memory: %p\n", ptr);

    int *arr_ptr = (int*)k_malloc(10*sizeof(int));
    printf("Address of allocated memory: %p\n", arr_ptr);

    int* ptr_2 = (int*)k_malloc(sizeof(int));
    printf("Address of allocated memory: %p\n", ptr_2);


    /*
        Once the PIC is initialized, interrupts can be enabled
    */

}







