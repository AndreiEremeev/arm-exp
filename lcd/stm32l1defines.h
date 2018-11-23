#define SRAM_BASE       0x20000000
#define STACK_TOP       (SRAM_BASE + 0x800)

#define RCC             0x40023800
#define RCC_AHBENR      (*(volatile unsigned long*)(RCC + 0x1c))
#define RCC_APB1ENR     (*(volatile unsigned long*)(RCC + 0x24))
#define RCC_APB2ENR     (*(volatile unsigned long*)(RCC + 0x20))
#define RCC_CSR         (*(volatile unsigned long*)(RCC + 0x34))
#define RCC_CSR_LSERDY  ((unsigned long)0x00000200)


#define GPIOA           0x40020000
#define GPIOA_MODER     (*(volatile unsigned long*)(GPIOA + 0x00))
#define GPIOA_OTYPER    (*(volatile unsigned long*)(GPIOA + 0x04))
#define GPIOA_PUPDR     (*(volatile unsigned long*)(GPIOA + 0x0c))
#define GPIOA_OSPEEDR   (*(volatile unsigned long*)(GPIOA + 0x08))
#define GPIOA_AFRL      (*(volatile unsigned long*)(GPIOA + 0x20))
#define GPIOA_AFRH      (*(volatile unsigned long*)(GPIOA + 0x24))

#define GPIOB           0x40020400
#define GPIOB_MODER     (*(volatile unsigned long*)(GPIOB + 0x00))
#define GPIOB_OTYPER    (*(volatile unsigned long*)(GPIOB + 0x04))
#define GPIOB_PUPDR     (*(volatile unsigned long*)(GPIOB + 0x0c))
#define GPIOB_OSPEEDR   (*(volatile unsigned long*)(GPIOB + 0x08))
#define GPIOB_AFRL      (*(volatile unsigned long*)(GPIOB + 0x20))
#define GPIOB_AFRH      (*(volatile unsigned long*)(GPIOB + 0x24))

#define GPIOC           0x40020800
#define GPIOC_MODER     (*(volatile unsigned long*)(GPIOC + 0x00))
#define GPIOC_OTYPER    (*(volatile unsigned long*)(GPIOC + 0x04))
#define GPIOC_PUPDR     (*(volatile unsigned long*)(GPIOC + 0x0c))
#define GPIOC_OSPEEDR   (*(volatile unsigned long*)(GPIOC + 0x08))
#define GPIOC_AFRL      (*(volatile unsigned long*)(GPIOC + 0x20))
#define GPIOC_AFRH      (*(volatile unsigned long*)(GPIOC + 0x24))

#define PWR             0x40007000
#define PWR_CR          (*(volatile unsigned long*)(PWR + 0x00))


#define LCD             0x40002400
#define LCD_CR          (*(volatile unsigned long*)(LCD + 0x00))
#define LCD_FCR         (*(volatile unsigned long*)(LCD + 0x04))
#define LCD_SR          (*(volatile unsigned long*)(LCD + 0x08))
#define LCD_SR_FCRSR    ((unsigned long)0x00000020)
#define LCD_SR_RDY      ((unsigned long)0x00000010)
#define LCD_SR_ENS      ((unsigned long)0x00000001)
#define LCD_SR_UDR      ((unsigned long)0x00000004)
#define LCD_RAM_COM0    (*(volatile unsigned  long *)(LCD + 0x14))
#define LCD_RAM_COM1    (*(volatile unsigned  long *)(LCD + 0x1c))
#define LCD_RAM_COM2    (*(volatile unsigned  long *)(LCD + 0x24))
#define LCD_RAM_COM3    (*(volatile unsigned  long *)(LCD + 0x2c))
#define LCD_RAM_COM4    (*(volatile unsigned  long *)(LCD + 0x34))
#define LCD_RAM_COM5    (*(volatile unsigned  long *)(LCD + 0x3c))
#define LCD_RAM_COM6    (*(volatile unsigned  long *)(LCD + 0x44))
#define LCD_RAM_COM7    (*(volatile unsigned  long *)(LCD + 0x4c))


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
