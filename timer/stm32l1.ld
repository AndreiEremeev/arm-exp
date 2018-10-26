MEMORY
{
    flash : org = 0x08000000, len = 128k
    ram0  : org = 0x20000000, len = 16k
}
 
/* output sections */
SECTIONS
{
    /* program code into FLASH */
    .text :
    {
        *(.vector_table)    /* Vector table */
        *(.text)            /* Program code */
    } >flash
 
    /* uninitialized global and static variables (which 
       we don't have any in this example) into SRAM */
    .data :
    {
        *(.data)            
    } >ram0
}   