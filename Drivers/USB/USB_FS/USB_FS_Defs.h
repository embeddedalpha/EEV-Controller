/*
 * USB_FS_Defs.h
 *
 *  Created on: Oct 6, 2024
 *      Author: kunal
 */

#ifndef USB_USB_FS_USB_FS_DEFS_H_
#define USB_USB_FS_USB_FS_DEFS_H_

#include "main.h"

#define USB_FS_In_Endpoint_Quantity 3
#define USB_FS_Out_Endpoint_Quantity 3

#define USB_OTG_FS_GLOBAL				((USB_OTG_GlobalTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_OTG_FS_DEVICE 				((USB_OTG_DeviceTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
#define USB_OTG_FS_HOST 				((USB_OTG_HostTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_BASE))
#define USB_OTG_FS_PCGCTL 				((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))
#define USB_OTG_FS_EP_REG_SIZE 			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_EP_REG_SIZE))
#define USB_OTG_FS_HOST_PORT 			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_PORT_BASE))
#define USB_OTG_FS_HOST_CHANNEL 		((USB_OTG_HostChannelTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_BASE))
#define USB_OTG_FS_HOST_CHANNEL_SIZE 	((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_SIZE))
#define USB_OTG_FS_FIFO				 	((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_FIFO_BASE))
#define USB_OTG_FS_FIFO_SIZE			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_FIFO_SIZE))
#define USB_OTG_FS_IN_ENDPOINT_0		((USB_OTG_INEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (0 * 0x20)))
#define USB_OTG_FS_IN_ENDPOINT_1		((USB_OTG_INEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (1 * 0x20)))
#define USB_OTG_FS_IN_ENDPOINT_2		((USB_OTG_INEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (2 * 0x20)))
#define USB_OTG_FS_IN_ENDPOINT_3		((USB_OTG_INEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE + (3 * 0x20)))
#define USB_OTG_FS_OUT_ENDPOINT_0		((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (0 * 0x20)))
#define USB_OTG_FS_OUT_ENDPOINT_1		((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (1 * 0x20)))
#define USB_OTG_FS_OUT_ENDPOINT_2		((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (2 * 0x20)))
#define USB_OTG_FS_OUT_ENDPOINT_3		((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE + (3 * 0x20)))



typedef struct USB_Modes{

	uint8_t Disable;
	uint8_t Dual_Role_Device;
	uint8_t Host;
	uint8_t Device;

}USB_Modes;


static const struct USB_FS_Configurations{

	USB_Modes Modes;

}USB_FS_Configurations = {

		.Modes =
		{
			.Disable 		  = 0x01,
			.Dual_Role_Device = 0x02,
			.Host             = 0x03,
			.Device           = 0x04,

		},

};


#endif /* USB_USB_FS_USB_FS_DEFS_H_ */
