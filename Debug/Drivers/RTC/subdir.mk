################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/RTC/RTC.c 

OBJS += \
./Drivers/RTC/RTC.o 

C_DEPS += \
./Drivers/RTC/RTC.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/RTC/%.o Drivers/RTC/%.su Drivers/RTC/%.cyclo: ../Drivers/RTC/%.c Drivers/RTC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Singal_Processing" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-RTC

clean-Drivers-2f-RTC:
	-$(RM) ./Drivers/RTC/RTC.cyclo ./Drivers/RTC/RTC.d ./Drivers/RTC/RTC.o ./Drivers/RTC/RTC.su

.PHONY: clean-Drivers-2f-RTC

