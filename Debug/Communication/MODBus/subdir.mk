################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Communication/MODBus/MODBus.c 

OBJS += \
./Communication/MODBus/MODBus.o 

C_DEPS += \
./Communication/MODBus/MODBus.d 


# Each subdirectory must supply rules for building sources it contributes
Communication/MODBus/%.o Communication/MODBus/%.su Communication/MODBus/%.cyclo: ../Communication/MODBus/%.c Communication/MODBus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Communication-2f-MODBus

clean-Communication-2f-MODBus:
	-$(RM) ./Communication/MODBus/MODBus.cyclo ./Communication/MODBus/MODBus.d ./Communication/MODBus/MODBus.o ./Communication/MODBus/MODBus.su

.PHONY: clean-Communication-2f-MODBus
