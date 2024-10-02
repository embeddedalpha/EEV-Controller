#include "main.h"
#include "GPIO/GPIO.h"
#include "USART/USART.h"


USART_Config Modbus_USART;

#define Modbus_RX_Buffer_Length 20

uint8_t Modbus_RX_Buffer_1[Modbus_RX_Buffer_Length];

uint16_t Modbus_Message_length = 0;

void USART1_IRQHandler(void)
{

		Modbus_USART.USART_DMA_Instance_RX.Request.Stream -> CR &= ~DMA_SxCR_EN;

		Modbus_Message_length = Modbus_RX_Buffer_Length - Modbus_USART.USART_DMA_Instance_RX.Request.Stream -> NDTR;

		static int temp = 0;
		temp = Modbus_USART.Port -> SR;
		USART_RX_Buffer(&Modbus_USART, &Modbus_RX_Buffer_1[0], Modbus_RX_Buffer_Length, 0);

		USART_TX_Buffer(&Modbus_USART, &Modbus_RX_Buffer_1[0], Modbus_Message_length);
}


int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	Modbus_USART.Port = USART1;
	Modbus_USART.RX_Pin = USART1_RX_Pin.PB7;
	Modbus_USART.TX_Pin = USART1_TX_Pin.PB6;
	Modbus_USART.baudrate = 9600;
	Modbus_USART.dma_enable =  USART_Configuration.DMA_Enable.RX_Enable | USART_Configuration.DMA_Enable.TX_Enable;
	Modbus_USART.hardware_flow = USART_Configuration.Hardware_Flow.Disable;
	Modbus_USART.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable |  USART_Configuration.Interrupt_Type.Receiver_Empty_Enable;
	Modbus_USART.mode = USART_Configuration.Mode.Asynchronous;
	Modbus_USART.parity = USART_Configuration.Parity_Type.Disable;
	Modbus_USART.stop_bits = USART_Configuration.Stop_Bits.Bit_1;

	USART_Init(&Modbus_USART);
	USART_RX_Buffer(&Modbus_USART, &Modbus_RX_Buffer_1[0], Modbus_RX_Buffer_Length, 0);



	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
			                 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);


//	General_Timer_Update_Init();


	for(;;)
	{

		GPIO_Pin_High(GPIOD, 12);
		Delay_s(1);
		GPIO_Pin_Low(GPIOD, 12);
		Delay_s(1);

	}
}



//
//

