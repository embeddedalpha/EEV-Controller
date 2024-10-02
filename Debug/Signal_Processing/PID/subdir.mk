################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Signal_Processing/PID/PID.c 

OBJS += \
./Signal_Processing/PID/PID.o 

C_DEPS += \
./Signal_Processing/PID/PID.d 


# Each subdirectory must supply rules for building sources it contributes
Signal_Processing/PID/%.o Signal_Processing/PID/%.su Signal_Processing/PID/%.cyclo: ../Signal_Processing/PID/%.c Signal_Processing/PID/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Signal_Processing-2f-PID

clean-Signal_Processing-2f-PID:
	-$(RM) ./Signal_Processing/PID/PID.cyclo ./Signal_Processing/PID/PID.d ./Signal_Processing/PID/PID.o ./Signal_Processing/PID/PID.su

.PHONY: clean-Signal_Processing-2f-PID

