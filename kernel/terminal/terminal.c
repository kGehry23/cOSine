
/**
 ********************************************************************************
 * @file    terminal.c
 *
 * @date    2025-12-21
 *
 * @brief   Functions for terminal writing/character placement and VGA setup.
 * 
 *          Credit: Adapted from https://wiki.osdev.org/Bare_Bones
 *      
 ********************************************************************************
 */

/************************************
 * INCLUDES
 ************************************/
#include "terminal.h"

/************************************
 * DEFINES
 ************************************/
#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

/************************************
 * ENUMS
 ************************************/
enum vga_colour
{
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/************************************
 * GLOBALS
 ************************************/
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
//Define a pointer to vram memory start location
uint16_t *terminal_buffer = (uint16_t*)VGA_MEMORY;

/*!
 * @brief Returns the number of elements in a provided character array
 * @param str Character pointer to check length of
 * @return Length of the pointed to character array
 */
size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

/*!
 * @brief Formats the selected background and foreground colours appropriately for use by the VGA
 * @param fg enum of vga foreground colours
 * @param bg enum of vga background colours 
 * @return 8 bit color for terminal output
 */
static inline uint8_t vga_entry_colour(enum vga_colour fg, enum vga_colour bg)
{
    return fg | bg << 4;
}

/*!
 * @brief Formats the selected text colour and text appropriately for use by the VGA
 * @param uc Character to display in the terminal
 * @param colour Colour of text to display
 * @return 16 bit character entry
 */
static inline uint16_t vga_entry(unsigned char uc, uint8_t colour)
{
    return (uint16_t)uc | (uint16_t)colour << 8;
}

/*!
 * @brief Clears the terminal window
 * @return None
 */
void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_colour = vga_entry_colour(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);

    //Clears the terminal
    for(size_t y = 0; y < VGA_HEIGHT; y++)
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            //Accesses each element in the vga memory space with row major indexing
            const size_t index = y * VGA_WIDTH + x;
            //Fills all locations with empty characters
            terminal_buffer[index] = vga_entry(' ', terminal_colour);
        }
}

/*!
 * @brief Sets the background colour of the terminal
 * @param colour Unsigned 8 bit integer representing the terminal background colour
 * @return None
 */
void terminal_setcolour(uint8_t colour)
{
    terminal_colour = colour;
}

/*!
 * @brief Places a character at a specified location in the terminal
 * @param c Character to write to the terminal
 * @param colour Colout of the character to write
 * @param x Row index of VGA memory
 * @param y Column index of VGA memory
 * @return None
 */
void terminal_putentryat(char c, uint8_t colour, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, colour);
}

/*!
 * @brief Places the specified character in the terminal window
 * @param c Character to write to the terminal
 * @return None
 */
void terminal_putchar(char c)
{
    //Handles newlines
    if(c == '\n')
    {
        //Forces text to appear at edge of screen
        terminal_column = -1;
        ++terminal_row;
    }
    //Handles the tab character (4 spaces)
    else if(c == '\t')
    {
        terminal_column += 4;
    }
    else
        terminal_putentryat(c, terminal_colour, terminal_column, terminal_row);

    
    //Wrap around back to index 0 if column or row index exceeds width
    if(++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

/*!
 * @brief Writes a string of characters to the terminal
 * @param data Character array to write to the terminal
 * @param size Number of elements in the character array
 * @return None
 */
void terminal_write(const char* data, size_t size)
{
    for(size_t i = 0; i < size; i++)
        terminal_putchar(data[i]);
}

/*!
 * @brief Writes a string of characters to the terminal
 * @param data Character array to write to the terminal
 * @return None
 */
void terminal_wrestling(const char* data)
{
    terminal_write(data, strlen(data));
}