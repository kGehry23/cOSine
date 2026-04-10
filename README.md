# cOSine

cOSine is a 32-bit operating system kernel for the IA-32 x86 architecture. The project is fully written in C and nasm-style x86 assembly, and uses QEMU as the emulation platform.

<br>

To date, the kernel is minimal but has implemented and has support for the following features:

- 32-bit paging  (default paging mode on IA-32 when enabled)
- Cooperative multitasking
- First come first served CPU scheduling
- Remapping of the Programmable Interrupt Controller (PIC)
- Initialization and setup of the Global Descriptor Table (GDT) and Interrupt Descriptor Table (IDT)
- Handling and setup of the Programmable Interval Timer (PIT)
- PS/2 driver and PS/2 keyboard driver 
- A simple ATA disk driver -> Sectors can be read and written
- A simple shell for interacting with the kernel

<br>

The kernel is being developed as a solo hobby project and has used the following resources in the process of development:

1. OSDev.org - https://wiki.osdev.org/Expanded_Main_Page
2. osdever.net - http://www.osdever.net/
3. Intel x86 Developer Manuals

<br>

*AI has not been used for any of the above development efforts

<br>


## Booting cOSine

To boot the kernel, the prebuilt GRUB bootloader has been used. This is done relatively simply by including the -kernel QEMU command line option. The intent is to write a bootloader myself, however, for initial development GRUB is being used.

<br>

Once in the root directory of the project, the included bash or power shell script can be run to build the kernel and launch QEMU to emulate x86.

In bash on windows use 

    ./make_boot_os.sh

or using powershell, run

    ./make_boot_os.ps1

This script will run the included make file which compiles or assembles all relevant files. A cross-compiler has not been setup for use in this project, but instead the nasm assembler and gcc with compiler flags of 

    -m32 -c -ffreestanding -nostdlib

has been used which compile the kernel as freestanding, without inclusion of the C standard library (provided by gcc), compiles for 32-bit, and does not link the resulting object files (-c).

<br>

On subsequent boots of the kernel, the second included bash or powershell script can be run, which simply launches QEMU using the perviously created kernel image (kernel.elf).


In bash on windows use

    ./boot_os.sh

or using powershell, run

    ./boos_os.ps1


<br>


## Creating Virtual Disk Image

If a fresh virtual disk is to be created, delete the original disk and run 

    qemu-img create -f qcow2 disk.img [disk size]

The disk size can be modified, however, the disk size selected in the included bash scripts is 100M (100 Mega Bytes).




