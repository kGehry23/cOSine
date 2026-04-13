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

/************************************
* INCLUDES
************************************/
#include "gdt.h"


/************************************
 * FUNCTION DEFINITIONS
 ************************************/

//Initializes a segment to be placed in the GDT
void init_segment(struct segment *seg, 
    unsigned int segment_number, 
    unsigned int seg_offset, 
    unsigned int seg_base,
    unsigned int seg_limit,
    uint8_t seg_access_byte,
    uint8_t seg_flags
    )
{
    seg->seg_num = segment_number;
    seg->offset = seg_offset;
    seg->base = seg_base;
    seg->limit = seg_limit;
    seg->access_byte = seg_access_byte;
    seg->flags = seg_flags;
}

/*!
 * @brief Encodes the GDT entries in the correct format
 * @param target Logical address of segment to add to table
 * @param source Segment to be added to GDT
 * @return None
 */
void encodedGDTEntry(uint8_t *target, struct segment source)
{
    //Encode limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;


    //Encode base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    //Encode access byte
    target[5] = source.access_byte;

    //Encode flags
    target[6] |= (source.flags << 4); 

}

/*!
 * @brief Performs initialization of the GDT
 * @return None
 */
void init_GDT(void)
{
    //Define GDT
    static uint8_t gdt[NUM_GDT_ENTRIES*GDT_ENTRY_SIZE];
    unsigned int gdt_size = (NUM_GDT_ENTRIES*GDT_ENTRY_SIZE) - 1; //Size of table in bytes subtracted by 1

    //Null segment descriptor 
    struct segment null_desc;
    init_segment(&null_desc, 0, 0x0000, 0, 0x00000, 0x00, 0x0);

    //Kernel mode code segment
    struct segment kernel_mode_code;
    init_segment(&kernel_mode_code, 1, 0x0008, 0, 0xFFFFF, 0x9A, 0xC);

    //Kernel mode data segment
    struct segment kernel_mode_data;
    init_segment(&kernel_mode_data, 2, 0x0010, 0, 0xFFFFF, 0x92, 0xC);
    
    uint8_t* null_desc_logical_addr = (uint8_t*)((uint32_t)&gdt + null_desc.offset);
    encodedGDTEntry(null_desc_logical_addr, null_desc);

    uint8_t* kernel_data_logical_addr = (uint8_t*)((uint32_t)&gdt + kernel_mode_data.offset);
    encodedGDTEntry(kernel_data_logical_addr, kernel_mode_data);

    uint8_t* kernel_code_logical_addr = (uint8_t*)((uint32_t)&gdt + kernel_mode_code.offset);
    encodedGDTEntry(kernel_code_logical_addr, kernel_mode_code);

    printf("Required descriptors added to GDT.\n");

    //Tells the cpu where the gdt is located 
    setGDT(gdt_size, (uint32_t)&gdt);

    //Reload segment registers
    reloadSegments();

    printf("Code and data segment registers reloaded.\n");
    printf("GDT loaded at address %p\n", &gdt);
}

