#include "main.h"
#include "USB/USB_FS/USB_FS_Driver.h"


USB_FS_Config testUSB;



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();


	testUSB.Mode = USB_FS_Configurations.Modes.Device;
	testUSB.SOF_Pin_Enable = 0;
	testUSB.VBUS_Pin_Enable = 0;

	USB_FS_Init(&testUSB);
	USB_FS_Connect(&testUSB);



	for(;;)
	{


	}
}



