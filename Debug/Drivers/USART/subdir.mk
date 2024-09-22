################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USART/USART.c 

OBJS += \
./Drivers/USART/USART.o 

C_DEPS += \
./Drivers/USART/USART.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USART/%.o Drivers/USART/%.su Drivers/USART/%.cyclo: ../Drivers/USART/%.c Drivers/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Singal_Processing" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-USART

clean-Drivers-2f-USART:
	-$(RM) ./Drivers/USART/USART.cyclo ./Drivers/USART/USART.d ./Drivers/USART/USART.o ./Drivers/USART/USART.su

.PHONY: clean-Drivers-2f-USART

