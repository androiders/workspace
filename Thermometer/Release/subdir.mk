################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../crc8.c \
../ds18x20.c \
../lcd.c \
../main.c \
../onewire.c 

OBJS += \
./crc8.o \
./ds18x20.o \
./lcd.o \
./main.o \
./onewire.o 

C_DEPS += \
./crc8.d \
./ds18x20.d \
./lcd.d \
./main.d \
./onewire.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -O2 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8515 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


