/*
 * USB_Device.h
 *
 *  Created on: Oct 7, 2024
 *      Author: kunal
 */

#ifndef USB_USB_FS_USB_DEVICE_H_
#define USB_USB_FS_USB_DEVICE_H_

#include "USB/USB_Standards.h"




typedef struct
{
	USB_Device_State Device_State;
	USB_Control_Transfer_Stage Control_Transfer_Stage;
	uint8_t configuration_Value;

	void const *ptr_out_buffer;
	void const *ptr_in_buffer;
	uint32_t in_data_size;
	uint32_t out_data_size;
}USB_Device;


#endif /* USB_USB_FS_USB_DEVICE_H_ */
