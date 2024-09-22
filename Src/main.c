#include "main.h"
#include "math.h"
#include "USART/USART.h"



USART_Config test;




int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	test.Port = USART1;

	test.RX_Pin = USART1_RX_Pin.PB7;
	test.TX_Pin = USART1_TX_Pin.PB6;
	test.baudrate = 9600;
	test.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable;
	test.hardware_flow = USART_Configuration.Hardware_Flow.Disable;
	test.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable;
	test.mode = USART_Configuration.Mode.Asynchronous;
	test.parity = USART_Configuration.Parity_Type.Disable;
	test.stop_bits = USART_Configuration.Stop_Bits.Bit_1;

	USART_Init(&test);



	for(;;)
	{


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
