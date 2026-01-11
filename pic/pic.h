#include "../libc/stdio/stdio.h"
#include "../io/io.h"

#define PIC_MASTER_BASE 0x20
#define PIC_SLAVE_BASE  0xA0

#define PIC_INIT    0x11

#define PIC_MASTER_COMMAND  PIC_MASTER_BASE
#define PIC_MASTER_DATA      (PIC_MASTER_BASE + 1)

#define PIC_SLAVE_COMMAND   PIC_SLAVE_BASE
#define PIC_SLAVE_DATA      (PIC_SLAVE_BASE + 1)

#define EOI 0x20

/*!
 * @brief Sends an end of interrupt command to a pic(s)
 * @param irq_number Number of the irq send the eoi for
 * @return None
 */
void PIC_eoi(uint8_t irq_number);

/*!
 * @brief Reinitializes the pic controllers
 * @param master_offset New offset for the master pic
 * @param slave_offset New offset for the slave pic
 * @return None
 */
void PIC_remap(uint8_t master_offset, uint8_t slave_offset);
