;################################################################
;	File Name: boot.asm
;	
;	Author: Kai Gehry
;	Date: 2025-12-19
;
;	Brief: Simple bootloader to load OS image from disk. 
;		   Written in x86 asm. 
;
;   Credit: Code adapted from Nir Lichtman
;			(https://www.youtube.com/watch?v=xFrMXzKCXIc)
;
;################################################################


bits 16			;running in real mode
org 0x7c00		;bios loads to this address in memory

mov si, 0		;move 0 into the si register. Used as counter for characters

print: 
	mov ah, 0x0e
	mov al, [bootmsg + si]	;call character printing interrupt
	int 0x10				;pass in character from memory
	add si, 1				
	cmp byte [bootmsg + si], 0
	jne print
	
jmp $

bootmsg: 
	db "Booted into cOSine", 0	;creates string to print

times 510 - ($ - $$) db 0	;pads with zeros to fit inside 512 byte sector
dw 0xAA55					;2 bytes as above is only 510. Needed for boot code to actually work (x86 magic)

