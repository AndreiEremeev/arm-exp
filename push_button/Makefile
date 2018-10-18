main.bin : main.elf
	arm-none-eabi-objcopy -Obinary main.elf main.bin
main.elf : main.o
	arm-none-eabi-ld  -Tstm32l1.ld -nostartfiles -o main.elf main.o
main.o : main.c
	arm-none-eabi-gcc -I. -fno-common -O0 -g -mcpu=cortex-m0 -mthumb -c -o main.o main.c
clean :
	rm main.bin main.elf main.o
