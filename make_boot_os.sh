# /**
#  ********************************************************************************
#  * @file    boot_qemu.sh
#  * @author  Kai Gehry
#  * @date    2026-01-10
#  *
#  * @brief   Compiles all files and boots qemu with os image.
#  ********************************************************************************
#  */

#Create empty disk image with
#
#       qemu-img create -f qcow2 disk.img 100M
#

#Boots into vm
eval "make clean;make"
# eval "qemu-system-i386 -kernel kernel.elf -monitor stdio -drive file=fat:rw:file_system,format=raw,media=disk"
eval "qemu-system-i386 -kernel kernel.elf -monitor stdio -hda disk.img"
