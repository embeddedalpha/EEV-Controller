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

void USB_FS_Init(USB_FS_Config *config);
void USB_FS_Connect(USB_FS_Config *config);
void USB_FS_Disconnect(USB_FS_Config *config);


#endif /* USB_USB_FS_USB_FS_DRIVER_H_ */
