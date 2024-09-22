################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Stepper_Motor/Stepper_Motor.c 

OBJS += \
./Drivers/Stepper_Motor/Stepper_Motor.o 

C_DEPS += \
./Drivers/Stepper_Motor/Stepper_Motor.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Stepper_Motor/%.o Drivers/Stepper_Motor/%.su Drivers/Stepper_Motor/%.cyclo: ../Drivers/Stepper_Motor/%.c Drivers/Stepper_Motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Singal_Processing" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-Stepper_Motor

clean-Drivers-2f-Stepper_Motor:
	-$(RM) ./Drivers/Stepper_Motor/Stepper_Motor.cyclo ./Drivers/Stepper_Motor/Stepper_Motor.d ./Drivers/Stepper_Motor/Stepper_Motor.o ./Drivers/Stepper_Motor/Stepper_Motor.su

.PHONY: clean-Drivers-2f-Stepper_Motor

