################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Communication/RS485/RS485.c 

OBJS += \
./Communication/RS485/RS485.o 

C_DEPS += \
./Communication/RS485/RS485.d 


# Each subdirectory must supply rules for building sources it contributes
Communication/RS485/%.o Communication/RS485/%.su Communication/RS485/%.cyclo: ../Communication/RS485/%.c Communication/RS485/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Communication-2f-RS485

clean-Communication-2f-RS485:
	-$(RM) ./Communication/RS485/RS485.cyclo ./Communication/RS485/RS485.d ./Communication/RS485/RS485.o ./Communication/RS485/RS485.su

.PHONY: clean-Communication-2f-RS485

