# /**
#  ********************************************************************************
#  * @file    boot_qemu.sh
#  * @author  Kai Gehry
#  * @date    2025-12-18
#  *
#  * @brief   Boots qemu with os image.
#  ********************************************************************************
#  */

#Change to kernel directory
cd "kernel"

#Assembles kernel assembly file
eval "nasm -f elf32 kernel.asm -o kernel_asm.o"
#Compiles basic kernel c file freestanding
eval "gcc -m32 -c kernel.c -o kernel_c.o -ffreestanding -nostdlib -nostdinc"
#Links asm object and c object files
eval "ld -T linker.ld -o kernel kernel_asm.o kernel_c.o -build-id=none"
#Converts linked object files to appropriate format
eval "objcopy -O elf32-i386 kernel kernel_boot.elf"
#Boots into vm
eval "qemu-system-i386 -kernel kernel_boot.elf"
