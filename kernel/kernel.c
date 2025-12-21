/**
 ********************************************************************************
 * @file    kernel.c
 * @author  Kai Gehry
 * @date    2025-12-20
 *
 * @brief   Basic kernel code.
 *      
 ********************************************************************************
 */

 void kernel(void)
 {
    const char *str = "Booted into cOSine"; //Initial message to print to screen

    char *vidptr = (char *)0xb8000; //Starting address of video memory
    unsigned int i = 1500; //Provides a starting position for new text to be displayed
    unsigned int j = 0; //Tracks string index


    //Prints string characters to screen
    while(str[j] != '\0')
    {
        vidptr[i] = str[j];

        vidptr[i+1] = 0x07;
        ++j;
        i = i+2;
    }

    return;

 }