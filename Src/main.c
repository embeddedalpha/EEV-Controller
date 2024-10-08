#include "main.h"
#include "USB/USB_FS/USB_Framework.h"


USB_Device testUSB;

uint32_t buffer[8];



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	testUSB.ptr_out_buffer = &buffer;

	USB_Initialize(&testUSB);



	for(;;)
	{
		USB_Poll();
	}
}



