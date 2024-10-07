/*
 * USB_Standards.h
 *
 *  Created on: Oct 5, 2024
 *      Author: kunal
 */

#ifndef USB_USB_STANDARDS_H_
#define USB_USB_STANDARDS_H_

typedef enum USB_EndpointType
{
	USB_Endpoint_Type_Control,
	USB_Endpoint_Type_Isochronous,
	USB_Endpoint_Type_Bulk,
	USB_Endpoint_Type_Interrupt,
}USB_EndpointType;

#endif /* USB_USB_STANDARDS_H_ */
