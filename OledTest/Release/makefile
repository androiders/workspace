################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Libraries/TinyWireM/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/androiders/workspace/OledTest/Release/arduino.ar \

ELF += \
OledTest.elf \

EEP += \
OledTest.eep \

FLASH_IMAGE += \
OledTest.hex \


# All Target
all: OledTest

# Tool invocations
OledTest: $(FLASH_IMAGE)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	${JANTJE.SIZE.SWITCH}
	@echo 'Finished building target: $@'
	@echo ' '

/home/androiders/workspace/OledTest/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	$(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

OledTest.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	$(LINK_OBJ) $(AR)
	@echo 'Finished building: $@'
	@echo ' '

OledTest.eep: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

OledTest.hex: $(EEP)
	@echo 'Create Flash image (ihex format)'
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELF)$(C++_DEPS)$(AR)$(C_DEPS)$(CC_DEPS)$(FLASH_IMAGE)$(AR_OBJ)$(CPP_DEPS)$(LINK_OBJ)$(EEP)$(CXX_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) OledTest
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
