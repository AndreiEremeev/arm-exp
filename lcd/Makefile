main.bin : main.elf
	arm-none-eabi-objcopy -Obinary main.elf main.bin
main.elf : main.o lcd.o
	arm-none-eabi-ld  -Tstm32l1.ld -nostartfiles -o main.elf main.o lcd.o
main.o : main.c
	arm-none-eabi-gcc -I. -fno-common -O0 -g -mcpu=cortex-m0 -mthumb -c -o main.o main.c
lcd.o : lcd.c
	arm-none-eabi-gcc -I. -fno-common -O0 -g -mcpu=cortex-m0 -mthumb -c -o lcd.o lcd.c
clean :
	rm main.bin main.elf main.o lcd.o
burn :
	st-flash write main.bin 0x8000000
