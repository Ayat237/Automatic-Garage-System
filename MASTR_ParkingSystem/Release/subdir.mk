################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DIO_PROG.c \
../LCD_Program.c \
../SPI_Prog.c \
../TIMER1_Prog.c \
../UART_Prog.c \
../main.c 

OBJS += \
./DIO_PROG.o \
./LCD_Program.o \
./SPI_Prog.o \
./TIMER1_Prog.o \
./UART_Prog.o \
./main.o 

C_DEPS += \
./DIO_PROG.d \
./LCD_Program.d \
./SPI_Prog.d \
./TIMER1_Prog.d \
./UART_Prog.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


