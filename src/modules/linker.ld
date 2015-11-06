/*  Bei _start soll die Ausfuehrung losgehen */
ENTRY(_start)

/*
 * Hier wird festgelegt, in welcher Reihenfolge welche Sektionen in die Binary
 * geschrieben werden sollen
 */
SECTIONS
{
    . = 0x8000000;
    .text : {
        *(moduleData)
        *(.text)
    }
    .data : {
        *(.data)
    }
    .rodata : {
        *(.rodata)
    }
    .bss : {
        *(.bss)
    }
    
    . = ALIGN(4096);
}

