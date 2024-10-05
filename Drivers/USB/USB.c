/*
 * USB.c
 *
 *  Created on: Oct 4, 2024
 *      Author: kunal
 */


#include "USB.h"


void USB_Device_Init(void)
{
	RCC -> AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
	while(!(RCC -> AHB2ENR & RCC_AHB2ENR_OTGFSEN));

	GPIO_Pin_Init(GPIOA, 11, GPIO_Configuration.Mode.Alternate_Function,
			                 GPIO_Configuration.Output_Type.Push_Pull,
							 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None,
							 GPIO_Configuration.Alternate_Functions.OTG_FS_1);
	GPIO_Pin_Init(GPIOA, 12, GPIO_Configuration.Mode.Alternate_Function,
			                 GPIO_Configuration.Output_Type.Push_Pull,
							 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.None,
							 GPIO_Configuration.Alternate_Functions.OTG_FS_1);



}
