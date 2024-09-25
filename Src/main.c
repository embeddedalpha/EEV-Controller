#include "main.h"
#include "math.h"
#include "USART/USART.h"
#include "GPIO/GPIO.h"
#include "Console/Console.h"




int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
//	Console_Init(9600);



	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
			                 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);




	for(;;)
	{


		GPIO_Pin_High(GPIOD, 12);
		Delay_s(1);
		GPIO_Pin_Low(GPIOD, 12);
		Delay_s(1);

	}
}


//void TIM6_DAC_IRQHandler(void)
//{
//	TIM6 -> SR &= ~TIM_SR_UIF;
//
//}
//
//
//void General_Timer_Update_Init(void)
//{
//	RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN;
//	TIM6->PSC = 8400-1;
//	TIM6->ARR = 100-1;
//	TIM6 -> EGR |= TIM_EGR_UG;
//	TIM6->CR1 |= TIM_CR1_URS;
//	TIM6->DIER |=  TIM_DIER_UIE;
//	TIM6->CR1 |= TIM_CR1_CEN;
//	NVIC_SetPriority(TIM6_DAC_IRQn,1);
//	NVIC_EnableIRQ(TIM6_DAC_IRQn);
//}
