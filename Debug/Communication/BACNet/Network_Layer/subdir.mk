################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Communication/BACNet/Network_Layer/NPDU.c 

OBJS += \
./Communication/BACNet/Network_Layer/NPDU.o 

C_DEPS += \
./Communication/BACNet/Network_Layer/NPDU.d 


# Each subdirectory must supply rules for building sources it contributes
Communication/BACNet/Network_Layer/%.o Communication/BACNet/Network_Layer/%.su Communication/BACNet/Network_Layer/%.cyclo: ../Communication/BACNet/Network_Layer/%.c Communication/BACNet/Network_Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Communication-2f-BACNet-2f-Network_Layer

clean-Communication-2f-BACNet-2f-Network_Layer:
	-$(RM) ./Communication/BACNet/Network_Layer/NPDU.cyclo ./Communication/BACNet/Network_Layer/NPDU.d ./Communication/BACNet/Network_Layer/NPDU.o ./Communication/BACNet/Network_Layer/NPDU.su

.PHONY: clean-Communication-2f-BACNet-2f-Network_Layer

