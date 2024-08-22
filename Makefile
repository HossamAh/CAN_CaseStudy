# makefile "Hossam Ahmed"

CC=arm-none-eabi-
CFLAGS= -mcpu=cortex-m3  -mthumb -gdwarf-2
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
SRC+= COTS/MCAL/GPIO/GPIO_program.c
SRC+= COTS/MCAL/RCC/RCC_program.c
SRC+= COTS/MCAL/AFIO/AFIO_program.c
SRC+= COTS/MCAL/CAN/CAN_program.c
OBJ=$(SRC:.c=.o)
AS=$(wildcard *.s)
ASOBJ=$(AS:.s=.o)
Project_name=STM32F103c6_scratch
all: $(Project_name).bin
	cp $(Project_name).elf $(Project_name).axf
	@echo "========== Project build is done =========="
$(Project_name).bin:$(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld  $(OBJ) $(ASOBJ) $(LIBS) -o $(Project_name).elf  -Map=Map_file.map
%.o:%.c 
	$(CC)gcc.exe -c  $(CFLAGS) $(INCS) $< -o $@

#startup.o:startup.s 
#	$(CC)as.exe $(CFLAGS) $< -o $@	
clean_all:
	rm COTS/MCAL/GPIO/*.o
	rm COTS/MCAL/RCC/*.o
	rm COTS/MCAL/AFIO/*.o
	rm COTS/MCAL/CAN/*.o
	rm *.o *.bin *.map *.elf *.axf
clean:
	rm -r *.elf *.bin