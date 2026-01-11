/**
 ********************************************************************************
 * File    linker.ld
 * 
 * Date    2025-12-20
 *
 * Brief   Memory map and format specs for kernel
 *      
 ********************************************************************************
 */


OUTPUT_FORMAT(pei-i386)
ENTRY(entry)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		_text_start = .;
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
		_end_data = .;
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		_sbss = .;		/*start of bss section*/
		*(COMMON)
		*(.bss)
		_ebss = .;		/*end of bss section*/	
		_endkernel = .;	/*Heap memory can begin here*/
	}
}