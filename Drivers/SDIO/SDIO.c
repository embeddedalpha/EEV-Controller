/*
 * SDIO.c
 *
 *  Created on: Oct 12, 2024
 *      Author: kunal
 */

#include "SDIO.h"


static const struct SD_Card_Commands
{
	uint32_t CMD0_GO_IDLE_STATE;
	uint32_t CMD8_SEND_IF_COND;
	uint32_t CMD55_APP_CMD;

	uint32_t ACMD41_SD_SEND_OP_COND;
	uint32_t CMD2_ALL_SEND_CID;
	uint32_t CMD3_SEND_RELATIVE_ADDR;

	uint32_t CMD7_SELECT_DESELECT_CARD;
	uint32_t CMD16_SET_BLOCKLEN;
	uint32_t CMD17_READ_SINGLE_BLOCK;

	uint32_t CMD18_READ_MULTIPLE_BLOCK;
	uint32_t CMD24_WRITE_BLOCK;
	uint32_t CMD25_WRITE_MULTIPLE_BLOCK;

	uint32_t CMD12_STOP_TRANSMISSION;
	uint32_t CMD9_SEND_CSD;
	uint32_t CMD13_SEND_STATUS;

	uint32_t ACMD6_SET_BUS_WIDTH;
	uint32_t ACMD22_SEND_NUM_WR_BLOCKS;
	uint32_t ACMD23_SET_WR_BLK_ERASE_COUNT;

	uint32_t ACMD51_SEND_SCR;

}SD_Card_Commands = {

		.CMD0_GO_IDLE_STATE = 0x00000000,
		.CMD8_SEND_IF_COND  = 0x000001AA,
		.CMD55_APP_CMD      = 0x00000000,
		.ACMD41_SD_SEND_OP_COND = 0x40FF8000,
		.CMD2_ALL_SEND_CID =0x00000000,
		.CMD3_SEND_RELATIVE_ADDR = 0x00000000,
		.CMD7_SELECT_DESELECT_CARD = 0x00000000,
};

#define SDIO_Prescaler_Init 126 //Sets the clock to 365Khz
#define SDIO_Prescaler_Debug 10 //Sets the clock to 4Mhz
#define SDIO_Prescaler_Production 0 //Sets the clock to 24Mhz


static const struct WAITRESP
{
	uint8_t No_Response_1;
	uint8_t Short_Response;
	uint8_t No_Response_2;
	uint8_t Long_Response;
}WAITRESP = {
		.No_Response_1 =  0,
		.Short_Response = 1 << 6,
		.No_Response_2 = 2 << 6,
		.Long_Response = 3 << 6,
};

typedef struct SDIO_Command_Format{
	bool CE_ATACMD;
	bool nIEN;
	bool ENCMDcompl;
	bool SDIOSuspend;
	bool CPSMEN;
	bool WAITPEND;
	bool WAITINT;
	uint8_t WAITRESP;
	uint8_t CMDINDEX;
}SDIO_Command_Format;

SDIO_Command_Format Command_Format;

static void Send_SDIO_Argument(uint32_t command)
{
	SDIO -> ARG = command;
}

static uint32_t Get_SDIO_Argument(void)
{
	return SDIO -> ARG;
}


static int8_t Set_Bus_Mode(SDIO_Config *config)
{


	return 1;
}

int8_t SDIO_Init(SDIO_Config *config)
{
	RCC -> APB2ENR |= RCC_APB2ENR_SDIOEN;



	GPIO_Pin_Init(GPIOD, 2, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
	GPIO_Pin_Init(GPIOC, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);

	if(config->Mode & SDIO_Configurations.Mode.SD1_or_MMC1)
	{

		GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		SDIO -> CLKCR &= ~SDIO_CLKCR_WIDBUS;
	}
	else if(config->Mode & SDIO_Configurations.Mode.SD4_or_MMC4)
	{
		GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);

		SDIO -> CLKCR |= SDIO_CLKCR_WIDBUS_0;
	}
	else if(config->Mode & SDIO_Configurations.Mode.MMC8)
	{
		GPIO_Pin_Init(GPIOC, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOB, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOB, 9, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 6, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);
		GPIO_Pin_Init(GPIOC, 7, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.Pull_Up, GPIO_Configuration.Alternate_Functions.SDIO_1);

		SDIO -> CLKCR |= SDIO_CLKCR_WIDBUS_1;
	}
	else{
		return -1;
	}

}

void SDIO_Power_Off(SDIO_Config *config)
{
	SDIO->POWER &= ~SDIO_POWER_PWRCTRL;
}
void SDIO_Power_On(SDIO_Config *config)
{
	SDIO->POWER |= SDIO_POWER_PWRCTRL;
}
