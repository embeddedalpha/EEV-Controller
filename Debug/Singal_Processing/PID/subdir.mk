################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Singal_Processing/PID/PID.c 

OBJS += \
./Singal_Processing/PID/PID.o 

C_DEPS += \
./Singal_Processing/PID/PID.d 


# Each subdirectory must supply rules for building sources it contributes
Singal_Processing/PID/%.o Singal_Processing/PID/%.su Singal_Processing/PID/%.cyclo: ../Singal_Processing/PID/%.c Singal_Processing/PID/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Singal_Processing" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Singal_Processing-2f-PID

clean-Singal_Processing-2f-PID:
	-$(RM) ./Singal_Processing/PID/PID.cyclo ./Singal_Processing/PID/PID.d ./Singal_Processing/PID/PID.o ./Singal_Processing/PID/PID.su

.PHONY: clean-Singal_Processing-2f-PID

