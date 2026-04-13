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


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

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

/*!
 * @brief Returns the contents of the combined contents of the master and
 *        slave PIC IRR or ISR registers. Higher 8 bits are PIC2 register contents,
 *        lower 8 bits are PIC1 contents
 * @return None
 */
uint16_t get_pic_status(uint16_t pic_reg)
{
    outb(PIC_MASTER_COMMAND, pic_reg);
    outb(PIC_SLAVE_COMMAND, pic_reg);

    return (inb(PIC_SLAVE_COMMAND) << 8) | inb(PIC_MASTER_COMMAND);
}

/*!
 * @brief Returns the contents of the combined contents of the master and
 *        slave PIC IRR registers. Higher 8 bits are PIC2 register contents,
 *        lower 8 bits are PIC1 contents
 * @return None
 */
uint16_t get_pic_irr()
{
    return get_pic_status(PIC_IRR);
}

/*!
 * @brief Returns the contents of the combined contents of the master and
 *        slave PIC ISR registers. Higher 8 bits are PIC2 register contents,
 *        lower 8 bits are PIC1 contents
 * @return None
 */
uint16_t get_pic_isr()
{
    return get_pic_status(PIC_ISR);
}

/*!
 * @brief Masks an irq
 * @param irq_number Number of the irq to mask
 * @return None
 */
void mask_pic_irq(uint8_t irq_number)
{
    uint8_t port;

    //IRQ belongs to the master PIC
    if(irq_number < 8)
        port = PIC_MASTER_DATA;
    
    //IRQ belongs to slave PIC
    else
    {
        irq_number -= 8;
        port = PIC_SLAVE_DATA;
    }
    
    //Update the mask bitmap
    outb(port, (inb(port) | (0x01<<irq_number)));
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