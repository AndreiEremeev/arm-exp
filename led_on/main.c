#define SRAM_BASE       0x20000000
#define STACK_TOP       (SRAM_BASE + 0x800)

#define RCC             0x40023800
#define RCC_AHBENR      (*(unsigned long*)(RCC + 0x1c))


#define GPIOB           0x40020400
#define GPIOB_MODER     (*(unsigned long*)(GPIOB + 0x00))
#define GPIOB_ODR       (*(unsigned long*)(GPIOB + 0x14))

void main();
unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)STACK_TOP,  // initial stack pointer 
    (unsigned long *)main        // main as Reset_Handler
};

void delay() {
    for(volatile int i=0; i<100000 ;++i);
}
void main() {
  RCC_AHBENR |= 1<<1;

  //little delay for GPIOB get ready
  volatile unsigned long i=0;
  i++; i++; i++;
  i=0;
  
  //Set PB6 PB7 as General purpose output 
  GPIOB_MODER &= ~((1 << 15) + (1 << 13));
  GPIOB_MODER |= (1 << 14) + (1 << 12);
  //turn on PB7
  GPIOB_ODR |= 1 << 7;
  
  while(1) {
    //Turn PB6
    GPIOB_ODR |= 1 << 6;
    //Turn PB7 off 
    GPIOB_ODR &= ~(1 << 7);
    delay();
    //Turn PB6 off
    GPIOB_ODR &= ~(1 << 6);
    GPIOB_ODR |= 1 << 7;
    delay();
  }
}
