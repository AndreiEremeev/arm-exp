#define SRAM_BASE       0x20000000
#define STACK_TOP       (SRAM_BASE + 0x800)

#define RCC             0x40023800
#define RCC_AHBENR      (*(volatile unsigned long*)(RCC + 0x1c))
#define RCC_APB2ENR     (*(volatile unsigned long*)(RCC + 0x20))


#define GPIOB           0x40020400
#define GPIOB_MODER     (*(volatile unsigned long*)(GPIOB + 0x00))
#define GPIOB_ODR       (*(volatile unsigned long*)(GPIOB + 0x14))

#define GPIOA           0x40020000
#define GPIOA_MODER     (*(volatile unsigned long*)(GPIOA + 0x00))
#define GPIOA_ODR       (*(volatile unsigned long*)(GPIOA + 0x14))

#define EXTI            0x40010400
#define EXTI_IMR        (*(volatile unsigned long*)(EXTI + 0x00))
#define EXTI_RTSR       (*(volatile unsigned long*)(EXTI + 0x08))
#define EXTI_PR         (*(volatile unsigned long*)(EXTI + 0x14))

#define SYSCFG          0x40010000
#define SYSCFG_EXTICR1  (*(volatile unsigned long*)(SYSCFG + 0x08))

#define NVIC            0xE000E100
#define NVIC_ISER0      (*(volatile unsigned long*)(NVIC + 0x00))

#define TIM6            0x40001000
#define TIMx_CNT        (*(volatile unsigned long*)(NVIC + 0x00))

void delay() {
    for(volatile int i=0; i<100000 ;++i);
}
void main();
void button();
void default_handler();
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
    (unsigned long *)button
};

void button() {
    EXTI_PR |= 1;
    GPIOB_ODR |= (1 << 6);
    delay();
    delay();
    delay();
    GPIOB_ODR &= ~(1 << 6);
}
void default_handler() {
    delay();
}
void main() {
  //GPIOB GPIOA;
  RCC_AHBENR |= ((1<<1) + 1);
  //SYSCF
  RCC_APB2ENR |= 1;

  //little delay for GPIOB/A get ready
  volatile unsigned long i=0;
  i++; i++; i++;
  i=0;
  
  //Set PB6 PB7 as General purpose output 
  GPIOB_MODER &= ~((1 << 15) + (1 << 13));
  GPIOB_MODER |= (1 << 14) + (1 << 12);
  //Set PA0 as General purpose input
  GPIOA_MODER &= ~((1 << 1) + 1);
  EXTI_RTSR |= 1;
  EXTI_IMR  |= 1;
  SYSCFG_EXTICR1 &= ~(15);
  NVIC_ISER0 |= (1 << 6);
  
  while(1) {}
}
