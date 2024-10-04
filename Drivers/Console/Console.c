/*
 * Console.c
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */


#include "Console.h"

volatile int rx_get_flag = 0;
volatile int rx_flag = 0;

#define RX_Buffer_Length 100

volatile int RX_Length = 0;

char RX_Buffer[RX_Buffer_Length];

char TX_Buffer[RX_Buffer_Length];

USART_Config serial;

void UART4_IRQHandler(void)
{
	if(rx_get_flag == 1)
	{
		volatile uint32_t temp;

		temp = UART4 -> SR;
		temp = UART4 -> DR;

		serial.USART_DMA_Instance_RX.Request.Stream->CR &= ~DMA_SxCR_EN;

		RX_Length = RX_Buffer_Length - serial.USART_DMA_Instance_RX.Request.Stream->NDTR;

		serial.USART_DMA_Instance_RX.Request.Stream -> NDTR &= RX_Buffer_Length;
		serial.USART_DMA_Instance_RX.Request.Stream -> CR |= DMA_SxCR_EN;

		rx_flag = 1;
	}

}


 void Console_Init(int32_t baudrate)
{
	 USART_Config_Reset(&serial);
	 serial.Port = UART4;
	 serial.baudrate = baudrate;
	 serial.mode = USART_Configuration.Mode.Asynchronous;
	 serial.stop_bits = USART_Configuration.Stop_Bits.Bit_1;
	 serial.TX_Pin = UART4_TX_Pin.PC10;
	 serial.RX_Pin = UART4_RX_Pin.PC11;
	 serial.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable;
	 serial.dma_enable = USART_Configuration.DMA_Enable.TX_Enable | USART_Configuration.DMA_Enable.RX_Enable;
	 USART_Init(&serial);
}

 void printConsole(char *msg, ...)
{
	va_list args;
	va_start(args, msg);
	vsprintf(TX_Buffer, msg, args);
	uint16_t len = strlen(TX_Buffer);
	USART_TX_Buffer(&serial, &TX_Buffer[0], len);
}

int readConsole(const char *msg, ...)
{
	va_list args;
	int result;
	rx_get_flag = 1;
	USART_RX_Buffer(&serial, &RX_Buffer[0], RX_Buffer_Length, 0);
	while(rx_flag == 0){}
	RX_Buffer[RX_Length - 1] = 0;
	RX_Buffer[RX_Length - 2] = 0;
	va_start(args, msg);
	result = vsscanf(RX_Buffer,msg,args);
	va_end(args);
	rx_get_flag = 0;
	rx_flag = 0;
	return result;
}

