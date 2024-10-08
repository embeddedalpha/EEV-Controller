/*
 * USB_FS_Driver.h
 *
 *  Created on: Oct 6, 2024
 *      Author: kunal
 */

#ifndef USB_USB_FS_USB_FS_DRIVER_H_
#define USB_USB_FS_USB_FS_DRIVER_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "USB_FS_Defs.h"
#include "USB/USB_Standards.h"


typedef struct USB_FS_Config{
	uint8_t Mode;
	bool SOF_Pin_Enable;
	uint8_t VBUS_Pin_Enable;

}USB_FS_Config;

//void USB_FS_Init(USB_FS_Config *config);
//void USB_FS_Connect(USB_FS_Config *config);
//void USB_FS_Disconnect(USB_FS_Config *config);

typedef struct
{
	void (*initalize_Core)(USB_FS_Config *config);
	void (*connect)(USB_FS_Config *config);
	void (*disconnect)(USB_FS_Config *config);
	void (*flush_rxFIFO)(void);
	void (*flush_txFIFO)(uint8_t endPointNumber);
	void (*configure_in_endpoint)(uint8_t endPointNumber, USB_EndpointType endPointType, uint16_t endPointSize);
	void (*read_Packet)(void *buffer, uint16_t size);
	void (*write_Packet)(uint8_t endPointNumber, void const *buffer, uint16_t size);
	void (*poll)(void);
	void (*set_device_address)(uint8_t address);

}USB_Driver_Functions_Typedef;

extern const USB_Driver_Functions_Typedef USB_Driver_Functions;

extern USB_Event USB_Events;

#endif /* USB_USB_FS_USB_FS_DRIVER_H_ */
