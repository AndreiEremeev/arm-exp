#define SRAM_BASE       0x20000000
#define STACK_TOP       (SRAM_BASE + 0x800)

#define RCC_BASE        0x40023800
#define GPIOB_BASE      0x40020400

#define RCC_AHBENR      (*(volatile unsigned long*)(RCC_BASE + 0x1C))
#define GPIOB_MODER     (*(volatile unsigned long*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOB_BASE + 0x14))


int main(void);
 
/* vector table */
unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)STACK_TOP,  // initial stack pointer 
    (unsigned long *)main        // main as Reset_Handler
};

int main() {
    RCC_AHBENR |= 0x2;
    volatile unsigned long i=0;
    i++; i++; i++; i=0;

    GPIOB_MODER = (GPIOB_MODER & (~0x0000F000)) | (0x5000);
    GPIOB_ODR |= 0x40;

    while(1) {
    }
}
