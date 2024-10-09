################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Communication/BACNet/Data_Link_Layer/MSTP/MSTP.c 

OBJS += \
./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.o 

C_DEPS += \
./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.d 


# Each subdirectory must supply rules for building sources it contributes
Communication/BACNet/Data_Link_Layer/MSTP/%.o Communication/BACNet/Data_Link_Layer/MSTP/%.su Communication/BACNet/Data_Link_Layer/MSTP/%.cyclo: ../Communication/BACNet/Data_Link_Layer/MSTP/%.c Communication/BACNet/Data_Link_Layer/MSTP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Communication-2f-BACNet-2f-Data_Link_Layer-2f-MSTP

clean-Communication-2f-BACNet-2f-Data_Link_Layer-2f-MSTP:
	-$(RM) ./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.cyclo ./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.d ./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.o ./Communication/BACNet/Data_Link_Layer/MSTP/MSTP.su

.PHONY: clean-Communication-2f-BACNet-2f-Data_Link_Layer-2f-MSTP

