/*
 * USB_Defs.h
 *
 *  Created on: Oct 5, 2024
 *      Author: kunal
 */

#ifndef USB_USB_DEFS_H_
#define USB_USB_DEFS_H_

#include "main.h"

#define USB_OTG_FS_GLOBAL				((USB_OTG_GlobalTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_OTG_FS_DEVICE 				((USB_OTG_DeviceTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
#define USB_OTG_FS_IN_ENDPOINT			((USB_OTG_INEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE))
#define USB_OTG_FS_OUT_ENDPOINT			((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE))
#define USB_OTG_FS_HOST 				((USB_OTG_HostTypeDef *)		(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_BASE))
#define USB_OTG_FS_PCGCTL 				((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))
#define USB_OTG_FS_EP_REG_SIZE 			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_EP_REG_SIZE))
#define USB_OTG_FS_HOST_PORT 			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_PORT_BASE))
#define USB_OTG_FS_HOST_CHANNEL 		((USB_OTG_HostChannelTypeDef *)	(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_BASE))
#define USB_OTG_FS_HOST_CHANNEL_SIZE 	((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_SIZE))
#define USB_OTG_FS_FIFO				 	((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_FIFO_BASE))
#define USB_OTG_FS_FIFO_SIZE			((uint32_t *)					(USB_OTG_FS_PERIPH_BASE + USB_OTG_FIFO_SIZE))



#define USB_OTG_HS_GLOBAL				((USB_OTG_GlobalTypeDef *)		(USB_OTG_HS_PERIPH_BASE + USB_OTG_GLOBAL_BASE))
#define USB_OTG_HS_DEVICE				((USB_OTG_DeviceTypeDef *)		(USB_OTG_HS_PERIPH_BASE + USB_OTG_DEVICE_BASE))
#define USB_OTG_HS_IN_ENDPOINT			((USB_OTG_INEndpointTypeDef *)	(USB_OTG_HS_PERIPH_BASE + USB_OTG_IN_ENDPOINT_BASE))
#define USB_OTG_HS_OUT_ENDPOINT			((USB_OTG_OUTEndpointTypeDef *)	(USB_OTG_HS_PERIPH_BASE + USB_OTG_OUT_ENDPOINT_BASE))
#define USB_OTG_HS_HOST 				((USB_OTG_HostTypeDef *)		(USB_OTG_HS_PERIPH_BASE + USB_OTG_HOST_BASE))
#define USB_OTG_HS_PCGCTL 				((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_PCGCCTL_BASE))
#define USB_OTG_HS_EP_REG_SIZE 			((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_EP_REG_SIZE))
#define USB_OTG_HS_HOST_PORT 			((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_HOST_PORT_BASE))
#define USB_OTG_HS_HOST_CHANNEL 		((USB_OTG_HostChannelTypeDef *)	(USB_OTG_HS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_BASE))
#define USB_OTG_HS_HOST_CHANNEL_SIZE 	((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_HOST_CHANNEL_SIZE))
#define USB_OTG_HS_FIFO				 	((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_FIFO_BASE))
#define USB_OTG_HS_FIFO_SIZE			((uint32_t *)					(USB_OTG_HS_PERIPH_BASE + USB_OTG_FIFO_SIZE))


typedef struct USB_Roles{
	uint8_t Disable;
	uint8_t Dual_Role_Device;
	uint8_t Host;
	uint8_t Device;
}USB_Roles;

typedef struct USB_Modes{

	struct Full_Speed{
		USB_Roles Roles;
	}Full_Speed;

	struct High_Speed{
		USB_Roles Internal_Phy;
		USB_Roles External_Phy;
	}High_Speed;
}USB_Modes;


static const struct USB_Configurations{

	USB_Modes Modes;


}USB_Configurations = {

		.Modes =
		{
				.Full_Speed = {
						.Roles = {
								.Disable 		  = 0x01,
								.Dual_Role_Device = 0x02,
								.Host             = 0x03,
								.Device           = 0x04,
								},
							},

				.High_Speed = {
						.Internal_Phy = {
								.Disable 		  = 0x05,
								.Dual_Role_Device = 0x06,
								.Host             = 0x07,
								.Device           = 0x08,
								},

						.External_Phy = {
								.Disable 		  = 0x09,
								.Dual_Role_Device = 0x0A,
								.Host             = 0x0B,
								.Device           = 0x0C,
								},
						 },
		},





};

#endif /* USB_USB_DEFS_H_ */
