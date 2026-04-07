/**
 ********************************************************************************
 * @file    io.h
 * 
 * @author  Kai Gehry
 * @date    2025-12-30
 *
 * @brief   Header for reading and writing to I/O ports   
 * 
 ********************************************************************************
 */

/************************************
* INCLUDES
************************************/
#include <stdint.h>

#ifndef IO_H
#define IO_H

/*!
 * @brief Writes a byte an I/O port
 * @param port Port to write to
 * @param data Data to write to the port
 * @return None
 */
void outb(uint16_t port, uint8_t data);

/*!
 * @brief Reads a byte from an I/O port
 * @param port Port to read from
 * @return Byte available at port
 */
uint8_t inb(uint16_t port);


/*!
 * @brief Writes a byte an I/O port
 * @param port Port to write to
 * @param data Data to write to the port
 * @return None
 */
void outw(uint16_t port, uint16_t data);

/*!
 * @brief Reads a byte from an I/O port
 * @param port Port to read from
 * @return Byte available at port
 */
uint16_t inw(uint16_t port);


#endif //IO_H



