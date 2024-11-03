#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"

DMA_Config EEV1;
uint16_t buffer[600];


void Timer_1_Init();
void Timer_1_DeInit(void);
void Timer_1_Trigger(float freq);
void Move_Motor(uint16_t step, bool direction, float freq );
float frequency_normal  = 50.0;
float frequency_emergency = 150.0;


int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();


	GPIO_Pin_Init(GPIOA, 10, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);
	GPIO_Pin_Init(GPIOA,8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.TIM_1);


	EEV1.Request = DMA_Configuration.Request.TIM1_CH1;
	EEV1.circular_mode = DMA_Configuration.Circular_Mode.Disable;
	EEV1.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
	EEV1.memory_data_size = DMA_Configuration.Memory_Data_Size.half_word;
	EEV1.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.half_word;
	EEV1.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;
	EEV1.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
	EEV1.priority_level = DMA_Configuration.Priority_Level.Very_high;
	EEV1.transfer_direction = DMA_Configuration.Transfer_Direction.Memory_to_peripheral;
	EEV1.interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete | DMA_Configuration.DMA_Interrupts.Half_Transfer_Complete;


	DMA_Init(&EEV1);
	Timer_1_Init();

	for(int i = 0; i < 600; i++)
	{
		buffer[i] = 50;
	}

	for(;;)
	{
		Move_Motor(10, 0, frequency_normal);
		Delay_milli(1000);
		Move_Motor(450, 1, frequency_emergency);
		Delay_milli(1000);
		Move_Motor(450, 0, frequency_emergency);
		Delay_milli(1000);
		Move_Motor(50, 1, frequency_normal);
		Delay_milli(1000);

	}
}



void Move_Motor(uint16_t step, bool direction, float freq )
{


	buffer[step] = 0;
	Timer_1_Trigger(freq);
	EEV1.buffer_length = step+1;
	EEV1.memory_address = (uint32_t)&(buffer);
	EEV1.peripheral_address = (uint32_t)&(TIM1->CCR1);
	if(direction)
	{
		GPIO_Pin_High(GPIOA, 10);
	}
	else
	{
		GPIO_Pin_Low(GPIOA, 10);
	}
	DMA_Set_Target(&EEV1);
	DMA_Set_Trigger(&EEV1);
	while(TIM1_CH1_DMA_Flag.Transfer_Complete_Flag != true){}
	DMA_Reset_Flags(&TIM1_CH1_DMA_Flag);
	buffer[step] = 50;



}

void Timer_1_Trigger(float freq)
{
	TIM1 -> PSC = (168000000.0 / ((100.0)*freq))-1; // (168000000.0 / ((100.0)*frequency))-1
	TIM1 -> ARR = 100-1;
	TIM1 -> CR1 |= TIM_CR1_CEN;
}

void Timer_1_DeInit(void)
{
	RCC -> APB2ENR &= ~RCC_APB2ENR_TIM1EN;
	TIM1 -> CR1 &= ~TIM_CR1_CEN;
}

void Timer_1_Init()
{
	RCC -> APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1 -> BDTR |= TIM_BDTR_BKP | TIM_BDTR_MOE;
	TIM1 -> CCER |= TIM_CCER_CC1E;
	TIM1 -> EGR |= TIM_EGR_UG;
	TIM1 -> DMAR = 1;
	TIM1 -> DIER |= TIM_DIER_CC1DE;
}

