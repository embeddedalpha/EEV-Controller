################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Signal_Processing/PID/subdir.mk
-include Signal_Processing/Kalman_Filter/subdir.mk
-include Drivers/USB/USB_HS/subdir.mk
-include Drivers/USB/USB_FS/subdir.mk
-include Drivers/USB/Dummy_Folder/subdir.mk
-include Drivers/USART/subdir.mk
-include Drivers/Stepper_Motor/subdir.mk
-include Drivers/RTC/subdir.mk
-include Drivers/Logs/subdir.mk
-include Drivers/GPIO/subdir.mk
-include Drivers/DMA/subdir.mk
-include Drivers/Console/subdir.mk
-include Drivers/ADC/subdir.mk
-include Communication/MODBus/subdir.mk
-include Communication/BACNet/Network_Layer/subdir.mk
-include Communication/BACNet/Data_Link_Layer/MSTP/subdir.mk
-include Communication/BACNet/Application_Layer/subdir.mk
-include Application/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := EEV_Controller
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
EEV_Controller.elf \

MAP_FILES += \
EEV_Controller.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
EEV_Controller.list \


# All Target
all: main-build

# Main-build Target
main-build: EEV_Controller.elf secondary-outputs

# Tool invocations
EEV_Controller.elf EEV_Controller.map: $(OBJS) $(USER_OBJS) B:\STM32F407V_Firmware_C_Lang\EEV_Controller\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "EEV_Controller.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"B:\STM32F407V_Firmware_C_Lang\EEV_Controller\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="EEV_Controller.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

EEV_Controller.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "EEV_Controller.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) EEV_Controller.elf EEV_Controller.list EEV_Controller.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
