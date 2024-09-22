/*
 * Console.c
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */


#include "Console.h"


USART_Config serial;


 void Console_Init(int32_t baudrate)
{
	 USART_Config_Reset(&serial);
	 serial.Port = USART1;
	 serial.baudrate = baudrate;
	 serial.mode = USART_Configuration.Mode.Asynchronous;
	 serial.stop_bits = USART_Configuration.Stop_Bits.Bit_1;
	 serial.TX_Pin = USART1_TX_Pin.PB6;
	 serial.RX_Pin = USART1_RX_Pin.PB7;
	 serial.dma_enable = USART_Configuration.DMA_Enable.TX_Enable;
	 USART_Init(&serial);
}

 void printConsole(char *msg, ...)
{

	char buff[100];
//	DMA_Memory_To_Memory_Transfer(&x, 8, 8, &buff, 0, 1, 100);


	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	uint16_t len = strlen(buff);


	USART_TX_Buffer(&serial, &buff, len);

//	for(int i = 0; i<= strlen(buff)-1; i++)
//	{
//		serial.Port -> DR = buff[i];
//		while (!(serial.Port -> SR & USART_SR_TXE));
//	}
}

char readConsole(int buffer_length, char * msg, ...)
{
	char buff[100];
	va_list args;
	USART_RX_Buffer(&serial, &buff, buffer_length,false);
	va_start(args, msg);
    // Use sscanf to parse the input from the buffer
    int result = vsscanf(buff, msg, args);
    // Clean up the variable argument list
    va_end(args);
    return result;  // Return the number of successful conversions

}


