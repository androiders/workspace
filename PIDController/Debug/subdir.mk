################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../crc8.c \
../ds12887.c \
../ds18x20.c \
../lcd.c \
../onewire.c \
../pidcontroller.c 

OBJS += \
./crc8.o \
./ds12887.o \
./ds18x20.o \
./lcd.o \
./onewire.o \
./pidcontroller.o 

C_DEPS += \
./crc8.d \
./ds12887.d \
./ds18x20.d \
./lcd.d \
./onewire.d \
./pidcontroller.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O1 -fpack-struct -fshort-enums -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega8515 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


