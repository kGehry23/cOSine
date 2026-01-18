# /**
#  ********************************************************************************
#  * @file    makefile
#  * @author  Kai Gehry
#  * @date    2026-01-10
#  *
#  * @brief   Compiles or assembles all relevant kernel c and asm files
#  ********************************************************************************
#  */

#Compiler specification
CC=gcc
#Assembler specification
ASM=nasm
#Required compilation flags
CFLAGS= -m32 -c -ffreestanding -nostdlib

ASM_OBJS = kernel/kernel_asm.o gdt/gdt_asm.o idt/idt_asm.o io/io.o memory/paging/paging.o
C_OBJS = kernel/kernel.o kernel/tty/terminal.o libc/stdio/stdio.o libc/stdlib/stdlib.o libc/string/string.o gdt/gdt.o idt/idt.o memory/frame_allocator.o pic/pic.o drivers/ps2/ps2.o drivers/ps2/keyboard/keyboard.o memory/paging/pager.o

LINK_LIST = $(ASM_OBJS) $(C_OBJS) 

all: $(ASM_OBJS) $(C_OBJS) kernel.bin kernel.elf

#Compiles all .c files
$(C_OBJS): %.o: %.c 
	$(CC) -o $@ $< $(CFLAGS)

#Assembles as .asm files
$(ASM_OBJS): %.o: %.asm 
	$(ASM) -f elf32 -o $@ $<

#Links all object files
kernel.bin: $(LINK_LIST) 
	ld -T kernel/linker.ld -o kernel.bin $(LINK_LIST)

#Converts the generated binary to elf  
kernel.elf: kernel.bin
	objcopy -O elf32-i386 kernel.bin kernel.elf

clean:
	rm -f $(ASM_OBJS) 
	rm -f $(C_OBJS) 









