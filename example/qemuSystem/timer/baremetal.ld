/* Define memory layout */
SECTIONS
{
    /* Define the start address of the program */
    . = 0x80000000;

    /* Text section for code */
    .text : ALIGN(4) {
        *(.text.init)
        *(.text)              /* Place the rest of the program's code here */
        *(.rodata*)           /* Place read-only data (if any) */
    }
    . = ALIGN (CONSTANT (COMMONPAGESIZE));    

    /* Data section for initialized data */
    .data : {
        *(.data)              /* Initialized data goes here */
    }

}
