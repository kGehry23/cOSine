# /**
#  ********************************************************************************
#  * @file    boot_os.ps1
#  * @author  Kai Gehry
#  * @date    2026-04-07
#  *
#  * @brief   Boots qemu with os image.
#  ********************************************************************************
#  */

#Boots into vm
qemu-system-i386 -kernel kernel.elf -monitor stdio -hda disk.img
