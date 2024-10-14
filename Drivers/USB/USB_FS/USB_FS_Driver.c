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

inline static __IO uint32_t *FIFO_Address(uint8_t endPointNumber)
{
	return (__IO uint32_t *)(USB_OTG_FS_PERIPH_BASE + USB_OTG_FIFO_BASE + (endPointNumber * 0x1000));
}

static void USB_FS_Write_Packet(uint8_t endPointNumber, void const *buffer, uint16_t size)
{
	uint32_t *fifo = FIFO_Address(endPointNumber);

	USB_OTG_INEndpointTypeDef *in_endpoint = IN_Endpoint(endPointNumber);

	in_endpoint->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_PKTCNT | USB_OTG_DIEPTSIZ_XFRSIZ);
	in_endpoint->DIEPTSIZ |= (1 << USB_OTG_DIEPTSIZ_PKTCNT_Pos);
	in_endpoint->DIEPTSIZ |= (size << USB_OTG_DIEPTSIZ_XFRSIZ_Pos);

	in_endpoint->DIEPCTL &= ~(USB_OTG_DIEPCTL_STALL);
	in_endpoint->DIEPCTL |=  USB_OTG_DIEPCTL_EPENA | USB_OTG_DIEPCTL_CNAK;

	size = (size + 3)/4;

	for(; size > 0; size--, buffer += 4)
	{
		*fifo = *((uint32_t *)buffer);
	}


}

static void USB_FS_Read_Packet(void *buffer, uint16_t size)
{
	uint32_t *fifo = FIFO_Address(0);

	for(; size >= 4; size -= 4, buffer += 4)
	{
		uint32_t data = *fifo;
		*((uint32_t *)buffer) = data;
	}

	if(size > 0)
	{
		uint32_t data = *FIFO_Address(0);

		for(; size > 0; size--, buffer++, data >>= 8)
		{
			*((uint8_t*)buffer) = 0xFF & data;
		}
	}
}

static void USB_FS_Flush_RX_FIFO(void)
{
	USB_OTG_FS -> GRSTCTL |= USB_OTG_GRSTCTL_RXFFLSH;
}

static void USB_FS_Flush_TX_FIFO(uint8_t endPointNumber)
{
	USB_OTG_FS -> GRSTCTL &= ~USB_OTG_GRSTCTL_TXFNUM;
	USB_OTG_FS -> GRSTCTL |= (endPointNumber << USB_OTG_GRSTCTL_TXFNUM_Pos) & USB_OTG_GRSTCTL_TXFNUM_Msk;
	USB_OTG_FS -> GRSTCTL |= USB_OTG_GRSTCTL_TXFFLSH;
}


static void USB_FS_Refresh_FIFO_Start_Address(void)
{

	uint16_t start_address = ((USB_OTG_FS -> GRXFSIZ & USB_OTG_GRXFSIZ_RXFD_Msk)>>USB_OTG_GRXFSIZ_RXFD_Pos) * 4;

	USB_OTG_FS -> DIEPTXF0_HNPTXFSIZ |= (start_address << USB_OTG_TX0FSA_Pos) & USB_OTG_TX0FSA_Msk;

	start_address += ((USB_OTG_FS -> DIEPTXF0_HNPTXFSIZ  & USB_OTG_TX0FD_Msk) >> USB_OTG_TX0FD_Pos) * 4;

	for(uint8_t txFIFONumber = 0; txFIFONumber < USB_FS_In_Endpoint_Quantity -1; txFIFONumber++ )
	{
		USB_OTG_FS -> DIEPTXF[txFIFONumber] |= USB_OTG_NPTXFSA_Msk & (start_address << USB_OTG_NPTXFSA_Pos) ;

		start_address += ((USB_OTG_FS -> DIEPTXF[txFIFONumber] & USB_OTG_NPTXFD_Msk) >> USB_OTG_NPTXFD_Pos) * 4;
	}
}

static void USB_FS_Configure_RXFIFO_Size(uint16_t size)
{
	size = 10 + (2 * (size / 4)+1);
	USB_OTG_FS ->GRXFSIZ |= USB_OTG_GRXFSIZ_RXFD_Msk & (size <<  USB_OTG_GRXFSIZ_RXFD_Pos);

	USB_FS_Refresh_FIFO_Start_Address();
}

static void USB_FS_Configure_TXFIFO_Size(uint8_t endPointNumber,uint16_t size)
{
	size = (size + 3)/4;

	if(endPointNumber == 0)
	{
		USB_OTG_FS ->DIEPTXF0_HNPTXFSIZ |= USB_OTG_TX0FD_Msk & (size << USB_OTG_TX0FD_Pos);
	}
	else
	{
		USB_OTG_FS -> DIEPTXF[endPointNumber - 1] |= USB_OTG_NPTXFD_Msk & (size << USB_OTG_NPTXFD_Pos);
	}
	USB_FS_Refresh_FIFO_Start_Address();

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

	USB_FS_Configure_RXFIFO_Size(64);
	USB_FS_Configure_TXFIFO_Size(0, endpointSize);

}

static void USB_FS_Configure_In_Endpoints(uint8_t endPointNumber, USB_EndpointType endPointType, uint16_t endPointSize)
{
	USB_OTG_FS_DEVICE -> DAINTMSK |= (1 << endPointNumber);
	IN_Endpoint(endPointNumber) -> DIEPCTL &= ~(USB_OTG_DIEPCTL_MPSIZ | USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK | USB_OTG_DIEPCTL_EPTYP | USB_OTG_DIEPCTL_SD0PID_SEVNFRM | USB_OTG_DIEPCTL_TXFNUM);
	IN_Endpoint(endPointNumber) -> DIEPCTL |= USB_OTG_DIEPCTL_USBAEP | USB_OTG_DIEPCTL_SNAK  | USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
	IN_Endpoint(endPointNumber) -> DIEPCTL |= endPointSize << USB_OTG_DIEPCTL_MPSIZ_Pos;
	IN_Endpoint(endPointNumber) -> DIEPCTL |= endPointType << USB_OTG_DIEPCTL_EPTYP_Pos;
	IN_Endpoint(endPointNumber) -> DIEPCTL |= endPointNumber << USB_OTG_DIEPCTL_TXFNUM_Pos;
	USB_FS_Configure_TXFIFO_Size(endPointNumber, endPointSize);
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

	USB_FS_Flush_TX_FIFO(endPointNumber);
	USB_FS_Flush_RX_FIFO();

}


static void USB_FS_Init(USB_FS_Config *config)
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

	USB_OTG_FS_DEVICE -> DOEPMSK |= USB_OTG_DOEPMSK_XFRCM;
	USB_OTG_FS_DEVICE -> DIEPMSK |= USB_OTG_DIEPMSK_XFRCM;

	// High Speed USB will be worked on later
}

static void USB_FS_Connect(USB_FS_Config *config)
{
	USB_OTG_FS -> GCCFG |= USB_OTG_GCCFG_PWRDWN;
	USB_OTG_FS_DEVICE -> DCTL &= ~USB_OTG_DCTL_SDIS;
}

static void USB_FS_Disconnect(USB_FS_Config *config)
{
	USB_OTG_FS_DEVICE -> DCTL |= USB_OTG_DCTL_SDIS;
	USB_OTG_FS -> GCCFG &= ~USB_OTG_GCCFG_PWRDWN;
}

static void USB_FS_OEPINT_Handler()
{
	uint8_t endpoint_number = ffs(USB_OTG_FS_DEVICE -> DAINT)-1;
    if (IN_Endpoint(endpoint_number)->DIEPINT & USB_OTG_DIEPINT_XFRC)
    {
    	USB_Events.on_in_transfer_completed(endpoint_number);
    	IN_Endpoint(endpoint_number)->DIEPINT |= USB_OTG_DIEPINT_XFRC;
    }
}

static void USB_FS_RST_Handler()
{
	for(uint8_t i = 0; i <= USB_FS_Endpoint_Quantity; i++)
	{
		USB_FS_Deconfigure_In_Endpoints(i);
	}

	USB_Events.on_usb_reset_received();
}

static void USB_FS_ENUM_DONE_Handler()
{
	USB_FS_Configure_Endpoint_0(8);
}



static void USB_FS_RX_FIFOLV_Handler()
{
	uint32_t receive_packet_status = USB_OTG_FS -> GRXSTSP;

	uint8_t endPointNumber = (USB_OTG_GRXSTSP_EPNUM_Msk & receive_packet_status) >> USB_OTG_GRXSTSP_EPNUM_Pos;
	uint8_t byte_count     = (USB_OTG_GRXSTSP_BCNT_Msk & receive_packet_status) >> USB_OTG_GRXSTSP_BCNT_Pos;
	uint8_t packet_status  = (USB_OTG_GRXSTSP_PKTSTS_Msk & receive_packet_status) >> USB_OTG_GRXSTSP_PKTSTS_Pos;

	switch (packet_status) {

		case USB_GLOBAL_OUT_NAK:
		{

		}
			break;

		case USB_OUT_DATA_PACKET_RECEIVED:
		{

		}
			break;

		case USB_OUT_TRANSFER_COMPLETED:
		{
			OUT_Endpoint(endPointNumber) -> DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_CNAK;
		}
			break;

		case USB_SETUP_TRANSACTION_COMPLETED:
		{
			OUT_Endpoint(endPointNumber) -> DOEPCTL |= USB_OTG_DOEPCTL_EPENA | USB_OTG_DOEPCTL_CNAK;
		}
			break;

		case USB_SETUP_DATA_PACKET_RECEIVED:
		{
			USB_Events.on_setup_data_received(endPointNumber, byte_count);
		}
			break;

	}


}





static void USB_FS_Global_Status_Interrupt_Handler(void)
{
	volatile uint32_t gintsts = USB_OTG_FS -> GINTSTS;

	if(gintsts & USB_OTG_GINTSTS_USBRST)
	{
		USB_FS_RST_Handler();
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_USBRST;
	}
	else if(gintsts & USB_OTG_GINTSTS_ENUMDNE)
	{
		USB_FS_ENUM_DONE_Handler();
		USB_OTG_FS -> GINTSTS |= USB_OTG_GINTSTS_ENUMDNE;
	}
	else if(gintsts & USB_OTG_GINTSTS_RXFLVL)
	{
		USB_FS_RX_FIFOLV_Handler();
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

static void USB_FS_Set_Device_Address(uint8_t address)
{
	USB_OTG_FS_DEVICE -> DCFG &= ~USB_OTG_DCFG_DAD;
	USB_OTG_FS_DEVICE -> DCFG |= (address << USB_OTG_DCFG_DAD_Pos) & USB_OTG_DCFG_DAD_Msk;
}


const USB_Driver_Functions_Typedef USB_Driver_Functions = {
		.initalize_Core = &USB_FS_Init,
		.configure_in_endpoint = &USB_FS_Configure_In_Endpoints,
		.connect = &USB_FS_Connect,
		.disconnect = &USB_FS_Disconnect,
		.flush_rxFIFO = &USB_FS_Flush_RX_FIFO,
		.flush_txFIFO = &USB_FS_Flush_TX_FIFO,
		.read_Packet = &USB_FS_Read_Packet,
		.write_Packet = &USB_FS_Write_Packet,
		.poll = &USB_FS_Global_Status_Interrupt_Handler,
		.set_device_address = &USB_FS_Set_Device_Address,
};
