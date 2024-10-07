################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USB/USB_HS/USB_HS_Driver.c 

OBJS += \
./Drivers/USB/USB_HS/USB_HS_Driver.o 

C_DEPS += \
./Drivers/USB/USB_HS/USB_HS_Driver.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USB/USB_HS/%.o Drivers/USB/USB_HS/%.su Drivers/USB/USB_HS/%.cyclo: ../Drivers/USB/USB_HS/%.c Drivers/USB/USB_HS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-USB-2f-USB_HS

clean-Drivers-2f-USB-2f-USB_HS:
	-$(RM) ./Drivers/USB/USB_HS/USB_HS_Driver.cyclo ./Drivers/USB/USB_HS/USB_HS_Driver.d ./Drivers/USB/USB_HS/USB_HS_Driver.o ./Drivers/USB/USB_HS/USB_HS_Driver.su

.PHONY: clean-Drivers-2f-USB-2f-USB_HS

