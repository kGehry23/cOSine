; /**
;  ********************************************************************************
;  * File Name    kernel.asm
;  *      
;  * Date         2025-12-18
;  *
;  * Brief        Assembly file for stack setup and kernel main function call from
;  *              kernel.c. GRUB bootloader used to boot in Qemu.
;  *
;  *              Adapted from: https://arjunsreedharan.org/post/82710718100/
;  *                            kernels-101-lets-write-a-kernel
;  ********************************************************************************
;  */


bits 32         ;boots into 32 bit protected mode
global entry
extern _kernel  ;Allows for kernel function in kernel.c to be accessible

section .text
entry: jmp start

        align 4                  ;aligns on 4 byte boundary
        dd 0x1BADB002            ;magic
        dd 0x00                  ;flags
        dd - (0x1BADB002 + 0x00) ;checksum. magic+flags+checksum should be zero

start:
        cli
        mov esp, stack_space    ;sets stack pointer
        call _kernel            ;calls the kernel main function. _ is necessary
        hlt

section .bss
resb 8192                       ;defines 8 KB stack
stack_space: