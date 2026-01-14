/**
 ********************************************************************************
 * @file    pic.c
 * 
 * @author  Kai Gehry
 * @date    2026-01-12
 *
 * @brief   Function definitions for pic commands
 * 
 *          Adapted from: https://wiki.osdev.org/8259_PIC
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "pic.h"

/*!
 * @brief Sends an end of interrupt command to a pic(s)
 * @param irq_number Number of the irq the EOI command is sent for
 * @return None
 */
void PIC_eoi(uint8_t irq_number)
{
    if(irq_number >= 8)
        outb(PIC_SLAVE_COMMAND, EOI);

    outb(PIC_MASTER_COMMAND, EOI);
}



void get_pic_irr()
{

}

void get_pic_isr()
{

}


/*!
 * @brief Reinitializes the pic controllers
 * @return None
 */
void PIC_remap()
{
    //Initializes the master and slave pics
    outb(PIC_MASTER_COMMAND, PIC_INIT);
    outb(PIC_SLAVE_COMMAND, PIC_INIT);

    //Remaps the PIC
    outb(PIC_MASTER_DATA, PIC_MASTER_OFFSET);
    outb(PIC_SLAVE_DATA, PIC_SLAVE_OFFSET);

    //Tells the master PIC there is a slave at IRQ 2
    outb(PIC_MASTER_DATA, 1 << CASCADE_IRQ);
    //Tells slave its cascade identity
    outb(PIC_SLAVE_DATA, 2);

    //Make pics operate in 8086 mode 
    outb(PIC_MASTER_DATA, ICW4_8086);
    outb(PIC_SLAVE_DATA, ICW4_8086);

    //Unmask PICs
    outb(PIC_MASTER_DATA, 0);
    outb(PIC_SLAVE_DATA, 0);
}