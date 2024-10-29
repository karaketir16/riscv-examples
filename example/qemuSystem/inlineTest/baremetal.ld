/* Define memory regions */
MEMORY
{
  RAM (xrw) : ORIGIN = 0x80000000, LENGTH = 0x10000  /* 64 KB of RAM starting at 0x80000000 */
}

/* Set the entry point to _start */
ENTRY(_start)

SECTIONS
{
  /* Text section: place the code in memory */
  .text : {
    KEEP(*(.text._start))   /* Ensure the _start symbol is kept */
    *(.text*)               /* Include all .text sections */
  } > RAM                   /* Place in the RAM memory region (starts at 0x80000000) */

  /* Read-only data section (constants, etc.) */
  .rodata : { *(.rodata*) } > RAM

  /* Data section (initialized variables) */
  .data : { *(.data*) } > RAM

  /* BSS section (uninitialized variables) */
  .bss : { *(.bss*) } > RAM

  /* Define the stack section */
  .stack (NOLOAD) : {
    _stack_top = ORIGIN(RAM) + LENGTH(RAM);   /* Stack starts at the top of RAM (0x80010000 in this case) */
    _stack_bottom = _stack_top - 0x1000;      /* Reserve 4 KB for the stack */
  } > RAM
}

/* Provide symbols to indicate the start and end of the sections */
PROVIDE(_start_text = ADDR(.text));
PROVIDE(_end_text = ADDR(.text) + SIZEOF(.text));

PROVIDE(_start_rodata = ADDR(.rodata));
PROVIDE(_end_rodata = ADDR(.rodata) + SIZEOF(.rodata));

PROVIDE(_start_data = ADDR(.data));
PROVIDE(_end_data = ADDR(.data) + SIZEOF(.data));

PROVIDE(_start_bss = ADDR(.bss));
PROVIDE(_end_bss = ADDR(.bss) + SIZEOF(.bss));

/* Align the stack */
PROVIDE(_stack_align = 16);
