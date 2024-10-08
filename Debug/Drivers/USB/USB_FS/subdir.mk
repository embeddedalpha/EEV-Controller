################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/USB/USB_FS/USB_FS_Driver.c \
../Drivers/USB/USB_FS/USB_Framework.c 

OBJS += \
./Drivers/USB/USB_FS/USB_FS_Driver.o \
./Drivers/USB/USB_FS/USB_Framework.o 

C_DEPS += \
./Drivers/USB/USB_FS/USB_FS_Driver.d \
./Drivers/USB/USB_FS/USB_Framework.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/USB/USB_FS/%.o Drivers/USB/USB_FS/%.su Drivers/USB/USB_FS/%.cyclo: ../Drivers/USB/USB_FS/%.c Drivers/USB/USB_FS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Communication" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Refrigerant_Data" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Application" -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Signal_Processing" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-USB-2f-USB_FS

clean-Drivers-2f-USB-2f-USB_FS:
	-$(RM) ./Drivers/USB/USB_FS/USB_FS_Driver.cyclo ./Drivers/USB/USB_FS/USB_FS_Driver.d ./Drivers/USB/USB_FS/USB_FS_Driver.o ./Drivers/USB/USB_FS/USB_FS_Driver.su ./Drivers/USB/USB_FS/USB_Framework.cyclo ./Drivers/USB/USB_FS/USB_Framework.d ./Drivers/USB/USB_FS/USB_Framework.o ./Drivers/USB/USB_FS/USB_Framework.su

.PHONY: clean-Drivers-2f-USB-2f-USB_FS

