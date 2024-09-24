#include "main.h"
#include "math.h"
#include "USART/USART.h"
#include "GPIO/GPIO.h"
#include "Console/Console.h"


USART_Config test;

uint8_t buffer[15];

uint16_t length = 0;

int temp = 0;

#define RX_DMA_STREAM DMA2_Stream2
#define RX_DMA_CHANNEL 4

void USART1_IRQHandler(void)
{

	if((USART1 -> SR & USART_SR_RXNE) == USART_SR_RXNE)
	{
//		buffer[temp] = test.Port ->DR;
//		temp += 1;
		USART1 -> SR &= ~USART_SR_RXNE;
	}

	if((USART1 -> SR & USART_SR_IDLE) == USART_SR_IDLE)
	{
		test.USART_DMA_Instance_RX.Request.Stream -> CR &= ~DMA_SxCR_EN;

		length = 10-test.USART_DMA_Instance_RX.Request.Stream -> NDTR;
		int temp = test.Port -> SR;
	}
}



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
//	Console_Init(9600);

	test.Port = USART1;
	test.RX_Pin = USART1_RX_Pin.PB7;
	test.TX_Pin = USART1_TX_Pin.PB6;
	test.baudrate = 9600;
	test.dma_enable =  USART_Configuration.DMA_Enable.RX_Enable;
	test.hardware_flow = USART_Configuration.Hardware_Flow.Disable;
	test.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable |  USART_Configuration.Interrupt_Type.Receiver_Empty_Enable;
	test.mode = USART_Configuration.Mode.Asynchronous;
	test.parity = USART_Configuration.Parity_Type.Disable;
	test.stop_bits = USART_Configuration.Stop_Bits.Bit_1;

	USART_Init(&test);

	USART_RX_Buffer(&test, &buffer[0], 15, 0);


	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
			                 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);




	for(;;)
	{

//		printConsole("hello");

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
