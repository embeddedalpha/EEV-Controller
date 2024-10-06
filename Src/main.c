#include "main.h"
#include "USB/USB_Driver.h"


USB_Config testUSB;



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();


	testUSB.Mode = USB_Configurations.Modes.Full_Speed.Roles.Device;
	testUSB.SOF_Pin_Enable = 0;
	testUSB.VBUS_Pin_Enable = 0;

	USB_Init(&testUSB);
	USB_Connect(&testUSB);



	for(;;)
	{


	}
}



