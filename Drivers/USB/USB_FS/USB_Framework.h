/*
 * USB_Framework.h
 *
 *  Created on: Oct 7, 2024
 *      Author: kunal
 */

#ifndef USB_USB_FS_USB_FRAMEWORK_H_
#define USB_USB_FS_USB_FRAMEWORK_H_

#include "USB_FS_Driver.h"
#include "USB_Device.h"

void USB_Initialize(USB_Device *usb_device_config);
void USB_Poll(void);

#endif /* USB_USB_FS_USB_FRAMEWORK_H_ */
