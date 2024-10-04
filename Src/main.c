#include "main.h"
#include "GPIO/GPIO.h"
#include "Console/Console.h"



int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();
	Console_Init(9600);


	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
			                 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);



	volatile int ret_Scanf_temp = 0;
	int number1 = 0;
	int number2 = 0;
	int result = 0;

	for(;;)
	{
		printConsole("Please First Number X =  ");
		ret_Scanf_temp = readConsole("%d",&number1);
		printConsole("Please First Number Y =  ");
		ret_Scanf_temp = readConsole("%d",&number2);
		result = number1 + number2;
		printConsole("Final Answer = %d\r\n",result);
		printConsole("*******************************************************************\r\n");

//		GPIO_Pin_High(GPIOD, 12);
//		Delay_s(1);
//		GPIO_Pin_Low(GPIOD, 12);
//		Delay_s(1);

	}
}



