################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Singal_Processing/Kalman_Filter/Kalman_Filter.c 

OBJS += \
./Singal_Processing/Kalman_Filter/Kalman_Filter.o 

C_DEPS += \
./Singal_Processing/Kalman_Filter/Kalman_Filter.d 


# Each subdirectory must supply rules for building sources it contributes
Singal_Processing/Kalman_Filter/%.o Singal_Processing/Kalman_Filter/%.su Singal_Processing/Kalman_Filter/%.cyclo: ../Singal_Processing/Kalman_Filter/%.c Singal_Processing/Kalman_Filter/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Singal_Processing-2f-Kalman_Filter

clean-Singal_Processing-2f-Kalman_Filter:
	-$(RM) ./Singal_Processing/Kalman_Filter/Kalman_Filter.cyclo ./Singal_Processing/Kalman_Filter/Kalman_Filter.d ./Singal_Processing/Kalman_Filter/Kalman_Filter.o ./Singal_Processing/Kalman_Filter/Kalman_Filter.su

.PHONY: clean-Singal_Processing-2f-Kalman_Filter

