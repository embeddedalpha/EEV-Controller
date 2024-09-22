################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ADC/ADC.c 

OBJS += \
./Drivers/ADC/ADC.o 

C_DEPS += \
./Drivers/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ADC/%.o Drivers/ADC/%.su Drivers/ADC/%.cyclo: ../Drivers/ADC/%.c Drivers/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Singal_Processing" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-ADC

clean-Drivers-2f-ADC:
	-$(RM) ./Drivers/ADC/ADC.cyclo ./Drivers/ADC/ADC.d ./Drivers/ADC/ADC.o ./Drivers/ADC/ADC.su

.PHONY: clean-Drivers-2f-ADC

