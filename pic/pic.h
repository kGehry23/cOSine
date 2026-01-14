/**
 ********************************************************************************
 * @file    pic.h
 * 
 * @author  Kai Gehry
 * @date    2026-01-12
 *
 * @brief   Header for PIC commands
 * 
 *          Adapted from: https://wiki.osdev.org/8259_PIC
 *     
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "../libc/stdio/stdio.h"
#include "../io/io.h"

/************************************
 * DEFINES
 ************************************/
#define PIC_MASTER_BASE 0x20
#define PIC_SLAVE_BASE  0xA0

#define PIC_INIT    0x11

#define PIC_MASTER_COMMAND  PIC_MASTER_BASE
#define PIC_MASTER_DATA      (PIC_MASTER_BASE + 1)

//PIC remap offsets
#define PIC_MASTER_OFFSET   0x20
#define PIC_SLAVE_OFFSET    0x28

#define PIC_SLAVE_COMMAND   PIC_SLAVE_BASE
#define PIC_SLAVE_DATA      (PIC_SLAVE_BASE + 1)

#define EOI 0x20

#define ICW4_8086   0x01
#define CASCADE_IRQ 2


#ifndef PIC_H
#define PIC_H

/*!
 * @brief Sends an end of interrupt command to a pic(s)
 * @param irq_number Number of the irq send the eoi for
 * @return None
 */
void PIC_eoi(uint8_t irq_number);

void get_pic_irr(void);

void get_pic_isr(void);

/*!
 * @brief Reinitializes the pic controllers
 * @return None
 */
void PIC_remap(void);

#endif //PIC_H