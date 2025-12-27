/**
 ********************************************************************************
 * @file    gdt.c
 * 
 * @author  Kai Gehry
 * @date    2025-12-25
 *
 * @brief   Global descriptor table definition.
 *     
 ********************************************************************************
 */

#include <stdint.h>
#include "libc/stdio/stdio.h"


/*A struct describing the GDT whose address can be loaded 
  using the lgdt assembly instruction
*/
struct GDT
{
    unsigned int address;
    uint16_t size;
} __attribute__((packed));

//Struct which represents a GDT entry
struct segment
{
    unsigned int seg_num;
    uint16_t offset;
    unsigned int base;
    unsigned int limit;
    uint8_t access_byte;
    uint8_t flags;
};

//Initializes a segment to be placed in the GDT
void init_segment(struct segment seg, 
    unsigned int segment_number, 
    uint16_t seg_offset, 
    unsigned int seg_base,
    unsigned int seg_limit,
    uint8_t seg_access_byte,
    uint8_t seg_flags
    )
{
    seg.seg_num = segment_number;
    seg.offset = seg_offset;
    seg.base = seg_base;
    seg.limit = seg_limit;
    seg.access_byte = seg_access_byte;
    seg.flags = seg_flags;

}


void encodedGDTEntry(uint8_t *target, struct segment source)
{
    if(source.limit > 0xFFFFF)
        printf("GDT cannot encode limits larger than 0xFFFFF");

    //Encode limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.base >> 8) & 0xFF;
    //target[6] = (source.base >> 16) & 0x0F; //unsure of this... why & with 0x0F?


    //Encode base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    //Encode access byte
    target[5] = source.access_byte;

    //Encode flags
    //target[6] |= (source.flags << 4);  //also unsure here... why are we oring with the flag (likely need at least 8 bytes.. only using 4 for flag?)

}

void init_GDT()
{
    //Disables all interrupts
    asm volatile( "cli" );

    //Create and initialize null descriptor
    struct segment null_desc;
    init_segment(null_desc, 0, 0x0000, 0, 0x00000000, 0x00, 0x0);
    
    //Calculate logical address
    uint8_t* null_desc_logical_addr = (uint8_t*)(null_desc.seg_num*16 + null_desc.offset);
    //Encode and add null descriptor to GDT
    encodedGDTEntry(null_desc_logical_addr, null_desc);

}

