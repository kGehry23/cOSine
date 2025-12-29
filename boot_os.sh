# /**
#  ********************************************************************************
#  * @file    boot_qemu.sh
#  * @author  Kai Gehry
#  * @date    2025-12-18
#  *
#  * @brief   Boots qemu with os image.
#  ********************************************************************************
#  */

cd "kernel"
#Assembles kernel assembly file
eval "nasm -f elf32 kernel.asm -o kernel_asm.o"
#Compiles basic kernel c file freestanding
eval "gcc -m32 -c kernel.c -o kernel.o -ffreestanding -nostdlib"

cd "terminal"
#Compiles terminal functions file freestanding
eval "gcc -m32 -c terminal.c -o terminal.o -ffreestanding -nostdlib"

cd ".."
cd ".."
cd "libc/string"
#Compiles libc files freestanding
eval "gcc -m32 -c string.c -o string.o -ffreestanding -nostdlib"

cd ".."
cd "stdio"
eval "gcc -m32 -c stdio.c -o stdio.o -ffreestanding -nostdlib"

cd ".."
cd "stdlib"
eval "gcc -m32 -c stdlib.c -o stdlib.o -ffreestanding -nostdlib"

cd ".."
cd ".."
cd "gdt"
eval "nasm -f elf32 gdt.asm -o gdt_asm.o"
eval "gcc -m32 -c gdt.c -o gdt.o -ffreestanding -nostdlib"

cd ".."
cd "kernel"
#Links asm objects and c object files
eval "ld -T linker.ld -o kernel.bin kernel_asm.o kernel.o terminal/terminal.o ../libc/string/string.o ../libc/stdio/stdio.o ../libc/stdlib/stdlib.o ../gdt/gdt.o ../gdt/gdt_asm.o -build-id=none"
#Converts linked object files to appropriate format
eval "objcopy -O elf32-i386 kernel.bin kernel_boot.elf"
#Boots into vm
eval "qemu-system-i386 -kernel kernel_boot.elf"
