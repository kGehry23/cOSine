/**
 ********************************************************************************
 * File    linker.ld
 * 
 * Date    2025-12-20
 *
 * Brief   Memory map and format specs for kernel
 *      
 ********************************************************************************
 */


OUTPUT_FORMAT(pei-i386)
ENTRY(entry)
SECTIONS
{
    . = 0x100000;
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}