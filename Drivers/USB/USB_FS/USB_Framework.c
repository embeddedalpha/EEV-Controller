/*
 * USB_Framework.c
 *
 *  Created on: Oct 7, 2024
 *      Author: kunal
 */


#include "USB_Framework.h"

USB_FS_Config usb_core_handle;
USB_Device *usb_device_handle;

void USB_Initialize(USB_Device *usb_device_config)
{
	usb_device_handle = usb_device_config;

	usb_core_handle.Mode = USB_FS_Configurations.Modes.Device;
	usb_core_handle.SOF_Pin_Enable = 0;
	usb_core_handle.VBUS_Pin_Enable = 0;

	USB_Driver_Functions.initalize_Core(&usb_core_handle);
	USB_Driver_Functions.connect(&usb_core_handle);
}


void USB_Poll(void)
{
	USB_Driver_Functions.poll();
}

static void USB_Reset_Received_Handler(void)
{
	usb_device_handle -> in_data_size = 0;
	usb_device_handle -> out_data_size = 0;
	usb_device_handle -> configuration_Value = 0;
	usb_device_handle -> Device_State = USB_DEVICE_STATE_DEFAULT;
	usb_device_handle -> Control_Transfer_Stage = USB_CONTROL_STAGE_SETUP;
	USB_Driver_Functions.set_device_address(0);
}

#define GET_DESCRIPTOR 0

static void process_standard_device_request()
{
	USB_Requests const *request = usb_device_handle->ptr_out_buffer;

	switch (request -> bRequest)
	{
		case GET_DESCRIPTOR:
		{

		}
			break;
		default:
			break;
	}


}


static void USB_Process_Request()
{
	USB_Requests const *request = usb_device_handle->ptr_out_buffer;


	switch (request->bmRequestType & (USB_BM_REQUEST_TYPE_TYPE_MASK | USB_BM_REQUEST_TYPE_RECIPIENT_MASK))
	{
		case (USB_BM_REQUEST_TYPE_TYPE_STANDARD | USB_BM_REQUEST_TYPE_RECIPIENT_DEVICE):
		{

		}
			break;
	}
}


static void USB_Setup_Data_Received_Handler(uint8_t endPointNumber, uint8_t byteCount)
{

	USB_Driver_Functions.read_Packet(usb_device_handle->ptr_out_buffer, byteCount);

	Log_Print("Setup Data");
	for(int i = 0; i < byteCount; i++)
	{
		Log_Print("%d,",usb_device_handle->ptr_out_buffer++);
	}
	USB_Process_Request();

}



USB_Event USB_Events = {
		.on_usb_reset_received = &USB_Reset_Received_Handler,
		.on_setup_data_received = &USB_Setup_Data_Received_Handler,
};
