# /**
#  ********************************************************************************
#  * @file    boot_qemu.sh
#  * @author  Kai Gehry
#  * @date    2025-12-18
#  *
#  * @brief   Boots qemu with os image.
#  ********************************************************************************
#  */

#Change to qemu directory
cd "boot"

#Assemble boot assembly
eval "nasm boot.asm"
#Run qemu with os image
eval "qemu-system-i386 boot"