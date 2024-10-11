################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Logs/Logs.c 

OBJS += \
./Drivers/Logs/Logs.o 

C_DEPS += \
./Drivers/Logs/Logs.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Logs/%.o Drivers/Logs/%.su Drivers/Logs/%.cyclo: ../Drivers/Logs/%.c Drivers/Logs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Logs

clean-Drivers-2f-Logs:
	-$(RM) ./Drivers/Logs/Logs.cyclo ./Drivers/Logs/Logs.d ./Drivers/Logs/Logs.o ./Drivers/Logs/Logs.su

.PHONY: clean-Drivers-2f-Logs

