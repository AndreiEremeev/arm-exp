#define SRAM_BASE       0x20000000
#define STACK_TOP       (SRAM_BASE + 0x800)

#define RCC             0x40023800
#define RCC_AHBENR      (*(volatile unsigned long*)(RCC + 0x1c))
#define RCC_APB1ENR     (*(volatile unsigned long*)(RCC + 0x24))


#define GPIOB           0x40020400
#define GPIOB_MODER     (*(volatile unsigned long*)(GPIOB + 0x00))
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOB + 0x14))
#define GPIOB_IDR       (*(volatile unsigned long*)(GPIOB + 0x10))

#define NVIC            0xE000E100
#define NVIC_ISER1      (*(volatile unsigned long*)(NVIC + 0x04))

#define TIM6            0x40001000
#define TIM6_PSC        (*(volatile unsigned long*)(TIM6 + 0x28))
#define TIM6_ARR        (*(volatile unsigned long*)(TIM6 + 0x2c))
#define TIM6_DIER       (*(volatile unsigned long*)(TIM6 + 0x0c))
#define TIM6_SR         (*(volatile unsigned long*)(TIM6 + 0x10))
#define TIM6_CR1        (*(volatile unsigned long*)(TIM6 + 0x00))



void main();
void default_handler();
void timer_handler();
unsigned long *vector_table[] __attribute__((section(".vector_table"))) =
{
    (unsigned long *)STACK_TOP,  // initial stack pointer 
    (unsigned long *)main,        // main as Reset_Handler
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)default_handler,
    (unsigned long *)timer_handler,
};

void delay() {
    for(volatile int i=0; i<100 ;++i);
}
void default_handler() {
    delay();
}
void timer_handler() {
    TIM6_SR &= ~(1);
    if ( GPIOB_IDR == (GPIOB_IDR | (1 << 6)) ) {
        GPIOB_ODR &= ~(1 << 6);
    } else {
        GPIOB_ODR |= (1 << 6);
    }
}


void main() {
  //GPIOB ON;

  RCC_AHBENR |= (1<<1);
  //TIM6 ON
  RCC_APB1ENR |= (1<<4);

  //little delay for GPIOB get ready
  volatile unsigned long i=0;
  i++; i++; i++;
  i=0;
  
  GPIOB_MODER &= ~((1 << 15) + (1 << 13));
  GPIOB_MODER |= (1 << 14) + (1 << 12);

  TIM6_ARR = 1000;
  TIM6_PSC = 2000;
  TIM6_DIER |= 1;
  TIM6_CR1 |= 1;

  NVIC_ISER1 |= (1 << 11);
  //Set PB6 PB7 as General purpose output 
  
  while(1) {}
}
