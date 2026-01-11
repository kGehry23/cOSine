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

/*!
 * @brief Reinitializes the pic controllers
 * @param master_offset New offset for the master pic
 * @param slave_offset New offset for the slave pic
 * @return None
 */
void PIC_remap(uint8_t master_offset, uint8_t slave_offset)
{
    outb(PIC_MASTER_COMMAND, PIC_INIT);
    outb(PIC_SLAVE_COMMAND, PIC_INIT);

    outb(PIC_MASTER_DATA, master_offset);
    outb(PIC_SLAVE_DATA, slave_offset);



}