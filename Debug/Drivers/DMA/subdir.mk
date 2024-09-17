################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DMA/DMA.c 

OBJS += \
./Drivers/DMA/DMA.o 

C_DEPS += \
./Drivers/DMA/DMA.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DMA/%.o Drivers/DMA/%.su Drivers/DMA/%.cyclo: ../Drivers/DMA/%.c Drivers/DMA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/EEV_Controller/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-DMA

clean-Drivers-2f-DMA:
	-$(RM) ./Drivers/DMA/DMA.cyclo ./Drivers/DMA/DMA.d ./Drivers/DMA/DMA.o ./Drivers/DMA/DMA.su

.PHONY: clean-Drivers-2f-DMA

