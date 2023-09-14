################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_PROG.c \
../EX_INTERRUPT_Prog.c \
../GIE_Program.c \
../LCD_Program.c \
../SPI_Prog.c \
../TIMER1_Prog.c \
../TIMER_Prog.c \
../UART_Prog.c \
../main.c 

OBJS += \
./DIO_PROG.o \
./EX_INTERRUPT_Prog.o \
./GIE_Program.o \
./LCD_Program.o \
./SPI_Prog.o \
./TIMER1_Prog.o \
./TIMER_Prog.o \
./UART_Prog.o \
./main.o 

C_DEPS += \
./DIO_PROG.d \
./EX_INTERRUPT_Prog.d \
./GIE_Program.d \
./LCD_Program.d \
./SPI_Prog.d \
./TIMER1_Prog.d \
./TIMER_Prog.d \
./UART_Prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


