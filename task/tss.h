#include <stdint.h>

typedef struct
{
    //Segment selector for TSS of previous task
    uint16_t prev_task_link;

    //Offset into stack
    uint32_t esp0;
    uint32_t esp1;
    uint32_t esp2;

    //Stack segments
    uint16_t ss0;
    uint16_t ss1;
    uint16_t ss2;

    //Contains page directory address for the task
    uint32_t cr3;
    
    uint32_t eip; //Holds offset of next instruction
    uint32_t eflags; //CPU state
    uint32_t eax; //Accumulator register
    uint32_t ecx; //Counter register
    uint32_t edx; //Data register
    uint32_t ebx; //Base register
    uint32_t esp; //Stack pointer
    uint32_t ebp; //Stack base pointer
    uint32_t esi; //Source index register
    uint32_t edi; //Destination index register

    uint16_t es; //Additional segment register
    uint16_t cs; //Code segment
    uint16_t ss; //Stack segment
    uint16_t ds; //Additional segment register
    uint16_t fs; //Additional segment register
    uint16_t gs; //Additional segment register

    uint16_t ldt; //Local descriptor table segment selector

    uint32_t io_map_base_addr;

}task_state_segment;


void set_task_register(uint32_t tss_segment_addr);