/*
 * USB_Standards.h
 *
 *  Created on: Oct 5, 2024
 *      Author: kunal
 */

#ifndef USB_USB_STANDARDS_H_
#define USB_USB_STANDARDS_H_

#include "main.h"

typedef enum USB_EndpointType
{
	USB_Endpoint_Type_Control,
	USB_Endpoint_Type_Isochronous,
	USB_Endpoint_Type_Bulk,
	USB_Endpoint_Type_Interrupt,
}USB_EndpointType;

typedef enum USB_Device_Packet_Status
{
	USB_GLOBAL_OUT_NAK = 1,
	USB_OUT_DATA_PACKET_RECEIVED = 2,
	USB_OUT_TRANSFER_COMPLETED = 3,
	USB_SETUP_TRANSACTION_COMPLETED = 4,
	USB_SETUP_DATA_PACKET_RECEIVED = 6,
}USB_Device_Packet_Status;

typedef struct
{
	void (*on_usb_reset_received)();
	void (*on_setup_data_received)(uint8_t endPointNumber, uint8_t byteCount);
	void (*on_out_data_received)(uint8_t endPointNumber, uint8_t bcnt);
	void (*on_in_transfer_completed)(uint8_t endPointNumber);
	void (*on_out_transfer_completed)(uint8_t endPointNumber);
	void (*on_usb_polled)();
}USB_Event;

typedef enum
{
	USB_DEVICE_STATE_DEFAULT,
	USB_DEVICE_STATE_ADDRESSED,
	USB_DEVICE_STATE_CONFIGURED,
	USB_DEVICE_STATE_SUSPEND,
}USB_Device_State;

typedef enum
{
	USB_CONTROL_STAGE_SETUP,
	USB_CONTROL_STAGE_DATA_OUT,
	USB_CONTROL_STAGE_DATA_IN,
	USB_CONTROL_STAGE_DATA_IN_IDLE,
	USB_CONTROL_STAGE_DATA_IN_ZERO,
	USB_CONTROL_STAGE_STATUS_OUT,
	USB_CONTROL_STAGE_STATUS_IN,
}USB_Control_Transfer_Stage;

typedef struct
{
	uint8_t bmRequestType;
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} USB_Requests;

#define USB_BM_REQUEST_TYPE_DIRECTION_MSK		(1 << 7)
#define USB_BM_REQUEST_TYPE_DIRECTION_TODEVICE	(0 << 7)
#define USB_BM_REQUEST_TYPE_DIRECTION_TOHOST	(1 << 7)

#define USB_BM_REQUEST_TYPE_TYPE_MASK		(3 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_STANDARD	(0 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_CLASS		(1 << 5)
#define USB_BM_REQUEST_TYPE_TYPE_VENDOR		(2 << 5)

#define USB_BM_REQUEST_TYPE_RECIPIENT_MASK		(3 << 0)
#define USB_BM_REQUEST_TYPE_RECIPIENT_DEVICE	(0 << 0)
#define USB_BM_REQUEST_TYPE_RECIPIENT_INTERFACE	(1 << 0)
#define USB_BM_REQUEST_TYPE_RECIPIENT_ENDPOINT	(2 << 0)
#define USB_BM_REQUEST_TYPE_RECIPIENT_OTHER		(3 << 0)

#endif /* USB_USB_STANDARDS_H_ */
