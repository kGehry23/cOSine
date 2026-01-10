# /**
#  ********************************************************************************
#  * @file    boot_qemu.sh
#  * @author  Kai Gehry
#  * @date    2026-01-10
#  *
#  * @brief   Boots qemu with os image.
#  ********************************************************************************
#  */

#Boots into vm
eval "make clean;make "
eval "qemu-system-i386 -kernel kernel.elf -monitor stdio"
