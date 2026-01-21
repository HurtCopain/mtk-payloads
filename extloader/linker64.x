ENTRY(cmd_boot_to)
SECTIONS
{
    . = 0x201000;
    .text : {
        KEEP(*(.text.start))
        *(.text*)
    }
    .data : { *(.data*) }
    .bss : { *(.bss*) }
}
