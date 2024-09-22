/*
 * Stepper_Motor.c
 *
 *  Created on: Sep 21, 2024
 *      Author: kunal
 */


#include "Stepper_Motor.h"


DMA_Config Stepper_Motor;


#define array_length 2001
uint32_t data_array[array_length];

void Stepper_Motor_Init(void)
{

	for(int i = 0; i < array_length; i++)
	{
		data_array[i] = 0;
	}


	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable TIM5 clock
	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.TIM_4);

	Stepper_Motor.Request = DMA_Configuration.Request.TIM4_CH1;
	Stepper_Motor.circular_mode = DMA_Configuration.Circular_Mode.Disable;
	Stepper_Motor.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
	Stepper_Motor.interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete;
	Stepper_Motor.priority_level = DMA_Configuration.Priority_Level.Very_high;
	Stepper_Motor.transfer_direction = DMA_Configuration.Transfer_Direction.Memory_to_peripheral;

	Stepper_Motor.memory_data_size = DMA_Configuration.Memory_Data_Size.word;
	Stepper_Motor.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;

	Stepper_Motor.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
	Stepper_Motor.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.word;

	DMA_Init(&Stepper_Motor);

    TIM4 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    TIM4 -> CCMR1 |= TIM_CCMR1_OC1PE;
    TIM4 -> CCER |= TIM_CCER_CC1E;
    TIM4 -> DIER |= TIM_DIER_CC1DE;
//    TIM4->PSC = 84000000/(100*2000);                   // Prescaler
    TIM4->ARR = 100;                                   // Auto-reload value (period)
}


void Set_Stepper_Motor_Position(float control_signal, uint16_t speed)
{
    TIM4->PSC = 84000000/(100*speed)-1;
	for(int i = 0; i < array_length; i++)
	{
		data_array[i] = 0;
	}

	for(int i =0 ; i < (uint32_t)control_signal; i++)
	{
		data_array[i]= 50;
	}

	Stepper_Motor.memory_address = (uint32_t)&(data_array[0]);
	Stepper_Motor.peripheral_address = (uint32_t)&(TIM4->CCR1);
	Stepper_Motor.buffer_length = control_signal+1;
	DMA_Set_Target(&Stepper_Motor);
	DMA_Set_Trigger(&Stepper_Motor);

	TIM4 -> CR1 |= TIM_CR1_CEN;

	while(TIM4_CH1_DMA_Flag.Transfer_Complete_Flag != true){}
	DMA_Reset_Flags(&TIM4_CH1_DMA_Flag);

}
