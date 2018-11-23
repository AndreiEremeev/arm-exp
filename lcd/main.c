#include "stm32l1defines.h"
#include "lcd.h"

void main();

unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)STACK_TOP,  // initial stack pointer 
    (unsigned long *)main,        // main as Reset_Handler
};


void delay() {
    for(volatile int i=0; i<100000 ;++i);
}

void main() {
    prepare_lcd();
    prepare_lcd_controller();
    int minutes = 0;
    int hours   = 0;
    while(1) {
        delay();
        if (minutes >= 60) {
            minutes = 0;
            hours++;
        }
        print_time(hours, minutes);
        minutes++;
    }
}
