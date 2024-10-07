/*
 * USB_FS_Driver.c
 *
 *  Created on: Oct 6, 2024
 *      Author: kunal
 */



#include "USB_FS_Driver.h"

USB_FS_Config *dummyUSB;

inline static USB_OTG_INEndpointTypeDef * IN_Endpoint(uint8_t endpoint_number)
{
	return (USB_OTG_INEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (endpoint_number * 0x20));
}

inline static USB_OTG_OUTEndpointTypeDef * OUT_Endpoint(uint8_t endpoint_number)
{
	return (USB_OTG_OUTEndpointTypeDef *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (endpoint_number * 0x20));
}


static void USB_FS_Pins_Init(bool id_pin_enable, bool sof_pin_enable, bool vbus_pin_enable)
{
	// D+
	GPIO_Pin_Init(GPIOA, 11, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.OTG_FS_1);

	// D-
	GPIO_Pin_Init(GPIOA, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.OTG_FS_1);

	if(id_pin_enable)
	{
		GPIO_Pin_Init(GPIOA, 10, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.OTG_FS_1);
	}

	if(sof_pin_enable)
	{
		GPIO_Pin_Init(GPIOA, 8, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.OTG_FS_1);
	}

	if(vbus_pin_enable)
	{
		GPIO_Pin_Init(GPIOA, 9, GPIO_Configuration.Mode.Input, GPIO_Configuration.Output_Type.None, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);
	}
}


static void USB_FS_Configure_Endpoint_0( uint16_t endpointSize)
{
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << 0 | 1 << 16);

	IN_Endpoint(0) -> DIEPCTL &= ~(USB_OTG_DIEPCTL_MPSIZ | USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK);
	IN_Endpoint(0) -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK;
	IN_Endpoint(0) -> DIEPCTL |= endpointSize << USB_OTG_DIEPCTL_MPSIZ_Pos;
	OUT_Endpoint(0) -> DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_CNAK;
}

static void USB_FS_Configure_In_Endpoints(uint8_t endPointNumber, USB_EndpointType endPointType, uint16_t endPointSize)
{
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << endPointNumber);
	IN_Endpoint(endPointNumber) -> DIEPCTL &= ~(USB_OTG_DIEPCTL_MPSIZ | USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK | USB_OTG_DIEPCTL_EPTYP | USB_OTG_DIEPCTL_SD0PID_SEVNFRM);
	IN_Endpoint(endPointNumber) -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK  | USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
	IN_Endpoint(endPointNumber) -> DIEPCTL |= endPointSize << USB_OTG_DIEPCTL_MPSIZ_Pos;
	IN_Endpoint(endPointNumber) -> DIEPCTL |= endPointType << USB_OTG_DIEPCTL_EPTYP_Pos;
}

static void USB_FS_Deconfigure_In_Endpoints(uint8_t endPointNumber)
{
	USB_OTG_INEndpointTypeDef *in_endpoint = IN_Endpoint(endPointNumber);
	USB_OTG_OUTEndpointTypeDef *out_endpoint = OUT_Endpoint(endPointNumber);
	USB_OTG_FS_DEVICE -> DAINTMSK &= ~(1 << endPointNumber | 1 << endPointNumber);

	in_endpoint -> DIEPINT = 0x29FF;
	out_endpoint -> DOEPINT = 0x71FF;

	if(in_endpoint -> DIEPCTL & USB_OTG_DIEPCTL_EPENA)
	{
		in_endpoint -> DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
	}

	in_endpoint -> DIEPCTL &= ~USB_OTG_DIEPCTL_USBAEP;

	if(endPointNumber != 0)
	{
		if(out_endpoint -> DOEPCTL & USB_OTG_DOEPCTL_EPENA)
		{
			out_endpoint -> DOEPCTL |= USB_OTG_DOEPCTL_EPDIS;
		}

		out_endpoint -> DOEPCTL &= ~USB_OTG_DOEPCTL_USBAEP;
	}

}


void USB_FS_Init(USB_FS_Config *config)
{
	dummyUSB = config;

	if((config->Mode == USB_FS_Configurations.Modes.Device) || (config->Mode == USB_FS_Configurations.Modes.Host))
	{
		RCC -> AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
		while(!(RCC -> AHB2ENR & RCC_AHB2ENR_OTGFSEN)){}
		USB_FS_Pins_Init(0, config->SOF_Pin_Enable, config->VBUS_Pin_Enable);
	}
	else if(config->Mode == USB_FS_Configurations.Modes.Dual_Role_Device)
	{
		RCC -> AHB1ENR |= RCC_AHB2ENR_OTGFSEN;
		while(!(RCC -> AHB2ENR & RCC_AHB2ENR_OTGFSEN)){}
		USB_FS_Pins_Init(1, config->SOF_Pin_Enable, config->VBUS_Pin_Enable);
	}

	USB_OTG_FS -> GUSBCFG &= ~USB_OTG_GUSBCFG_TRDT_Msk;
	USB_OTG_FS -> GUSBCFG |= (0x06 << USB_OTG_GUSBCFG_TRDT_Pos) && USB_OTG_GUSBCFG_TRDT_Msk ;

	USB_OTG_FS -> GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;

	if(config->Mode == USB_FS_Configurations.Modes.Device)
	{
		USB_OTG_FS -> GUSBCFG &= ~USB_OTG_GUSBCFG_FDMOD_Msk;
		USB_OTG_FS -> GUSBCFG |=  USB_OTG_GUSBCFG_FDMOD;
	}
	else if(config->Mode == USB_FS_Configurations.Modes.Host)
	{
		USB_OTG_FS -> GUSBCFG &= ~USB_OTG_GUSBCFG_FHMOD_Msk;
		USB_OTG_FS -> GUSBCFG |=  USB_OTG_GUSBCFG_FHMOD;
	}


	USB_OTG_FS_DEVICE -> DCFG &= ~USB_OTG_DCFG_DSPD;
	USB_OTG_FS_DEVICE -> DCFG |=  USB_OTG_DCFG_DSPD;

	USB_OTG_FS -> GCCFG &= ~USB_OTG_GCCFG_VBUSBSEN;
	USB_OTG_FS -> GCCFG |=  USB_OTG_GCCFG_VBUSBSEN;

	USB_OTG_FS -> GINTMSK &= ~(USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_SOFM | USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_WUIM | USB_OTG_GINTMSK_IEPINT | USB_OTG_GINTMSK_RXFLVLM | USB_OTG_GINTSTS_OEPINT);
	USB_OTG_FS -> GINTMSK |= (USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_SOFM | USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_WUIM | USB_OTG_GINTMSK_IEPINT | USB_OTG_GINTMSK_RXFLVLM | USB_OTG_GINTSTS_OEPINT);

	USB_OTG_FS -> GINTSTS = 0xFFFFFFFF;

	USB_OTG_FS -> GAHBCFG |= USB_OTG_GAHBCFG_GINT;

	// High Speed USB will be worked on later
}

void USB_FS_Connect(USB_FS_Config *config)
{
	USB_OTG_FS -> GCCFG |= USB_OTG_GCCFG_PWRDWN;
	USB_OTG_FS_DEVICE -> DCTL &= ~USB_OTG_DCTL_SDIS;
}

void USB_FS_Disconnect(USB_FS_Config *config)
{
	USB_OTG_FS_DEVICE -> DCTL |= USB_OTG_DCTL_SDIS;
	USB_OTG_FS -> GCCFG &= ~USB_OTG_GCCFG_PWRDWN;
}

static void USB_FS_RST_Handler()
{

}

void USB_FS_Global_Status_Interrupt_Handler(void)
{
	volatile uint32_t gintsts = USB_OTG_FS -> GINTSTS;

	if(gintsts & USB_OTG_GINTSTS_USBRST)
	{
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_USBRST;
	}
	else if(gintsts & USB_OTG_GINTSTS_ENUMDNE)
	{
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_ENUMDNE;
	}
	else if(gintsts & USB_OTG_GINTSTS_RXFLVL)
	{
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_RXFLVL;
	}
	else if(gintsts & USB_OTG_GINTSTS_IEPINT)
	{
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_IEPINT;
	}
	else if(gintsts & USB_OTG_GINTSTS_OEPINT)
	{
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_OEPINT;
	}
}

