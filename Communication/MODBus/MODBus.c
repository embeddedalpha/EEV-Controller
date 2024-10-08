///*
// * MODBus.c
// *
// *  Created on: Sep 19, 2024
// *      Author: kunal
// */
//
//#include "MODBus.h"
//
//USART_Config Modbus_USART;
//
//Modbus_Config *Temp_Modbus_Config;
//
//#define Modbus_RX_Buffer_Length 300
//
//uint8_t Modbus_RX_Buffer_1[Modbus_RX_Buffer_Length];
//uint8_t Modbus_RX_Buffer_2[Modbus_RX_Buffer_Length];
//
//uint16_t Modbus_Message_length = 0;
//
//bool Modbus_Message_Received_Flag = 0;
//
//
//typedef enum {
//    MODBUS_SLAVE_IDLE,
//    MODBUS_RECEIVE_REQUEST,
//    MODBUS_VALIDATE_REQUEST,
//    MODBUS_PROCESS_REQUEST,
//    MODBUS_SEND_RESPONSE,
//    MODBUS_ERROR
//} ModbusSlaveState;
//
//// Initialize the state to IDLE
//ModbusSlaveState currentSlaveState = MODBUS_SLAVE_IDLE;
//
//
//void USART1_IRQHandler(void)
//{
//
//	if((Modbus_USART.Port  -> SR & USART_SR_RXNE) == USART_SR_RXNE)
//	{
//		Modbus_USART.Port  -> SR &= ~USART_SR_RXNE;
//	}
//
//	if((Modbus_USART.Port -> SR & USART_SR_IDLE) == USART_SR_IDLE)
//	{
//		Modbus_USART.USART_DMA_Instance_RX.Request.Stream -> CR &= ~DMA_SxCR_EN;
//
//		if((Modbus_RX_Buffer_1[0] == 0) || (Modbus_RX_Buffer_1[0] == Temp_Modbus_Config->slave_address))
//		{
//			Modbus_Message_length = Modbus_RX_Buffer_Length-Modbus_USART.USART_DMA_Instance_RX.Request.Stream -> NDTR;
//			Modbus_Message_Received_Flag = 1;
//		}
//		else
//		{
//			Modbus_Message_Received_Flag = 0;
//		}
//
//
//		static int temp = 0;
//		temp = Modbus_USART.Port -> SR;
//	}
//}
//
///* Table of CRC values for high–order byte */
//static unsigned char auchCRCHi[] = {
//	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
//	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
//	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
//	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
//	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
//	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
//	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
//	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
//	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
//	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
//	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
//	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
//	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
//	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
//	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
//	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
//	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
//	0x40
//} ;
//
//
///* Table of CRC values for low–order byte */
//static char auchCRCLo[] = {
//	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
//	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
//	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
//	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
//	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
//	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
//	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
//	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
//	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
//	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
//	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
//	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
//	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
//	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
//	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
//	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
//	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
//	0x40
//};
//
//
//
//
//static int Validate_Function_Code(ModBus_Frame *frame)
//{
//	if(frame->functionCode != MODBus_Functions.Read_Coil)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Read_Discrete_Inputs)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Read_Holding_Registers)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Read_Write_Mulitple_Registers)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Write_Single_Coil)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Write_Single_Register)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Write_Multiple_Coils)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else if(frame->functionCode != MODBus_Functions.Write_Multiple_Registers)
//	{
//		return MODBus_Exception_Code.Illegal_Function;
//	}
//	else
//	{
//		return  MODBus_Exception_Code.Illegal_Function;
//	}
//}
//
//
//static void Handle_Modbus_Error(ModBus_Frame *frame, uint8_t exception_code)
//{
//	uint8_t errorResponse[5];
//
//	errorResponse[0] = Temp_Modbus_Config->slave_address;
//	errorResponse[1] = frame->functionCode | 0x80;
//	errorResponse[2] = exception_code;
//	uint16_t errorCRC = ModBus_CRC16(&errorResponse, 3);
//	errorResponse[3] = errorCRC & 0xFF;
//	errorResponse[4] = (errorCRC >> 8) & 0xFF;
//
//	USART_TX_Buffer(&Modbus_USART, &errorResponse[0], 5);
//}
//
//
//unsigned short ModBus_CRC16(uint16_t *packet, uint16_t len)
//{
//    unsigned char uchCRCHi = 0xFF ; /* high byte of CRC initialized */
//    unsigned char uchCRCLo = 0xFF ; /* low byte of CRC initialized */
//    unsigned int uIndex ;           /* will index into CRC lookup table  */
//
//    unsigned int pointer = 0;
//    while(len--)
//    {
//        uIndex = uchCRCLo ^ packet[pointer++] ;
//        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
//        uchCRCHi = auchCRCLo[uIndex] ;
//    }
//
//    return (uchCRCHi << 8 | uchCRCLo) ;
//}
//
//
//int8_t Modbus_Init(Modbus_Config *config)
//{
//
//	Temp_Modbus_Config = config;
//	Modbus_USART.Port = USART1;
//	Modbus_USART.RX_Pin = USART1_RX_Pin.PB7;
//	Modbus_USART.TX_Pin = USART1_TX_Pin.PB6;
//	Modbus_USART.baudrate = 9600;
//	Modbus_USART.dma_enable =  USART_Configuration.DMA_Enable.RX_Enable;
//	Modbus_USART.hardware_flow = USART_Configuration.Hardware_Flow.Disable;
//	Modbus_USART.interrupt = USART_Configuration.Interrupt_Type.IDLE_Enable |  USART_Configuration.Interrupt_Type.Receiver_Empty_Enable;
//	Modbus_USART.mode = USART_Configuration.Mode.Asynchronous;
//	Modbus_USART.parity = USART_Configuration.Parity_Type.Disable;
//	Modbus_USART.stop_bits = USART_Configuration.Stop_Bits.Bit_1;
//
//	USART_Init(&Modbus_USART);
//	USART_RX_Buffer(&Modbus_USART, &Modbus_RX_Buffer_1[0], 15, 0);
//
//	return 1;
//}
//
//
//
//
//void Modbus_Slave_Run(void)
//{
//	static ModBus_Frame frame;
//	static int exception_code =0;
//
//	switch (currentSlaveState) {
//
//		case MODBUS_SLAVE_IDLE:
//		{
//			if(Modbus_Message_Received_Flag == 1)
//			{
//				currentSlaveState = MODBUS_RECEIVE_REQUEST;
//			}
//		}
//			break;
//
//		case MODBUS_RECEIVE_REQUEST:
//		{
//			frame.slaveAddress = Modbus_RX_Buffer_1[0];
//			frame.functionCode = Modbus_RX_Buffer_1[1];
//			frame.registerAddress = (Modbus_RX_Buffer_1[2] << 8) | (Modbus_RX_Buffer_1[3] << 0);
//			frame.numberOfRegisters = (Modbus_RX_Buffer_1[4] << 8) | (Modbus_RX_Buffer_1[5] << 0);
//			frame.crc = (Modbus_RX_Buffer_1[6] << 8) | (Modbus_RX_Buffer_1[7] << 0);
//
//			currentSlaveState = MODBUS_VALIDATE_REQUEST;
//		}
//		break;
//
//		case MODBUS_VALIDATE_REQUEST:
//		{
//			// Validate function Code
//
//			static uint8_t valid_flags = 0;
//
//
//
//		}
//		break;
//
//	}
//}
