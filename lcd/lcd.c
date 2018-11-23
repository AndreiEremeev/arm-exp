#include "stm32l1defines.h"

void prepare_lcd() {
    RCC_AHBENR |= 0x7;
    volatile unsigned long i=0;
    i++; i++; i++;
    //PA{1, 2, 3, 8, 9, 10, 15}
    //PB{3, 4, 5, 8, 9, 10, 11, 12, 13, 14, 15}
    //PC{0, 1, 2, 3, 6, 7, 8, 9, 10, 11}
    GPIOA_MODER |= 0x802A00A8;
    GPIOB_MODER |= 0xaaaa0a80;
    GPIOC_MODER |= 0xaaa0aa;

    GPIOA_OTYPER &= ~0x870E;
    GPIOB_OTYPER &= ~0xFF38;
    GPIOC_OTYPER &= ~0xFCF;
    GPIOA_PUPDR &= ~0xC03F00FC;
    GPIOB_PUPDR &= ~0xFFFF0FC0;
    GPIOC_PUPDR &= ~0xFFF0FF;
    GPIOA_OSPEEDR &= ~0xC03F00FC;
    GPIOB_OSPEEDR &= ~0xFFFF0FC0;
    GPIOC_OSPEEDR &= ~0xFFFFF0FF;

    GPIOA_AFRL |= 0xBBB0;
    GPIOA_AFRH |= 0xB0000BBB;
    GPIOB_AFRL |= 0xBBB000;
    GPIOB_AFRH |= 0xBBBBBBBB;
    GPIOC_AFRL |= 0xBB00BBBB;
    GPIOC_AFRH |= 0xBBBB;
}

void prepare_lcd_controller() {
    RCC_APB1ENR |= 0x10000200;
    PWR_CR |= 0x100;
    RCC_CSR |= 0x800000;
    RCC_CSR &= ~0x800000;
    RCC_CSR |= 0x100;
    while(!(RCC_CSR & RCC_CSR_LSERDY));
    RCC_CSR |= 0x10000;
    LCD_CR &= ~0x60;
    LCD_CR |= 0x40;
    LCD_CR &= ~0x1C;
    LCD_CR |= 0xC;
    LCD_CR |= 0x80;
    LCD_FCR &= ~0x3C00000;
    LCD_FCR &= ~0x3C0000;
    LCD_FCR |= 0x1040000;
    LCD_FCR &= ~0x1C00;
    LCD_FCR |= 0x800;
    while(!(LCD_SR & LCD_SR_FCRSR));
    LCD_CR &= ~0x2;
    LCD_CR |= 0x1;
    while(!(LCD_SR & LCD_SR_RDY));
    while(!(LCD_SR & LCD_SR_ENS));
}

void write_mask_to_lcd_ram (int position, unsigned int mask, int clear_before) {
	int P1,P2,P3,P4;
	if (position < 2) P1 = 2*position;
	else P1 = 2*position+4;
	
	if (position == 1) P2 = P1+5;
	else P2 = P1+1;
	
	if (position < 3) P3 = (23-2*position)+6;
	else P3 = (23-2*position)+4;
	
	if (position == 5) {
		P4 = P3;
		P3 -= 1;
	} else {
		P4 = P3 - 1;
	}

	unsigned long COM0,COM1,COM2,COM3;
	COM0 = LCD_RAM_COM0;
	COM1 = LCD_RAM_COM1;
	COM2 = LCD_RAM_COM2;
	COM3 = LCD_RAM_COM3;
	
	if (clear_before) {
		COM0&= ~(1<<P1 | 1<<P2 | 1<<P3 | 1<<P4);
		COM1&= ~(1<<P1 | 1<<P2 | 1<<P3 | 1<<P4);
		COM2&= ~(1<<P1 | 1<<P2 | 1<<P3 | 1<<P4);
		COM3&= ~(1<<P1 | 1<<P2 | 1<<P3 | 1<<P4);
	}
	
	COM0 |= ((mask >> 0x1) & 1) << P4 | ((mask >> 0x4) & 1) << P1
	      | ((mask >> 0x6) & 1) << P3 | ((mask >> 0xA) & 1) << P2;
	COM1 |= ((mask >> 0x0) & 1) << P4 | ((mask >> 0x2) & 1) << P2
	      | ((mask >> 0x3) & 1) << P1 | ((mask >> 0x5) & 1) << P3;
	COM3 |= ((mask >> 0x7) & 1) << P3 | ((mask >> 0x8) & 1) << P4
	      | ((mask >> 0xB) & 1) << P1 | ((mask >> 0xE) & 1) << P2;
	COM2 |= ((mask >> 0x9) & 1) << P4 | ((mask >> 0xC) & 1) << P1
	      | ((mask >> 0xD) & 1) << P3 | ((mask >> 0xF) & 1) << P2;

	LCD_RAM_COM0 = COM0;
	LCD_RAM_COM1 = COM1;
	LCD_RAM_COM2 = COM2;
	LCD_RAM_COM3 = COM3;
}

const int masks[10] = { 0x003F, 0x0006, 0x045B, 0x044F, 0x0466, 0x046D, 0x047D, 0x2201, 0x047F, 0x046F };
int mask(int number) {
    if(number > 9 ) {
        return 0;
    }
    return masks[number];
}

void print_time(int hours, int minutes) {
    int first = 0;
    int third = 0;

    while (hours >= 24) {
        hours -= 24;
    }

    while (minutes >= 60) {
        minutes -= 60;
    }

    while (hours >= 10) {
        ++first;
        hours -= 10;
    }
    int second = hours;

    while (minutes >= 10) {
        ++third;
        minutes -= 10;
    }
    int fourth = minutes;

    while(LCD_SR & LCD_SR_UDR) {};
	write_mask_to_lcd_ram (0, mask(first), 1);
	write_mask_to_lcd_ram (1, mask(second), 1);
	write_mask_to_lcd_ram (2, 0x8000, 1);
	write_mask_to_lcd_ram (4, mask(third), 1);
	write_mask_to_lcd_ram (5, mask(fourth), 1);
    LCD_SR |= LCD_SR_UDR;
}
