#include "main.h"
#include "math.h"
#include "USART/USART.h"
#include "GPIO/GPIO.h"
#include "Console/Console.h"

#include "../Signal_Processing/PID/PID.h"

#define Superheat_SetPoint 10

PID_Controller_Typedef EEV;

uint16_t Sensor_Array[2];



void TIM6_DAC_IRQHandler(void)
{
	TIM6 -> SR &= ~TIM_SR_UIF;

	float pressure = Get_Pressure();
	float temp_kel = Get_Temperature();

	float saturation_temp = Get_Saturation_Temp_From_Pressure(pressure, R454B_Saturation_Table, R545B_Table_Size);

	float superheat_cal = temp_kel - saturation_temp;

	PID_Controller_Update(&EEV, superheat_cal);

}

void General_Timer_Update_Init(void)
{
	RCC -> APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->PSC = 8400-1;
	TIM6->ARR = 100-1;
	TIM6 -> EGR |= TIM_EGR_UG;
	TIM6->CR1 |= TIM_CR1_URS;
	TIM6->DIER |=  TIM_DIER_UIE;
	TIM6->CR1 |= TIM_CR1_CEN;
	NVIC_SetPriority(TIM6_DAC_IRQn,1);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}


int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	EEV.T_Sampling_Time = 1/100.0f;
	EEV.Limit_Max = 2000;
	EEV.Limit_Min = 0;
	EEV.tau = 0.001;
	EEV.setpoint = Superheat_SetPoint;

	PID_Controller_Init(&EEV);




//	Console_Init(9600);



	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.General_Purpose_Output, GPIO_Configuration.Output_Type.Push_Pull,
			                 GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.None);

	General_Timer_Update_Init();


	for(;;)
	{


		GPIO_Pin_High(GPIOD, 12);
		Delay_s(1);
		GPIO_Pin_Low(GPIOD, 12);
		Delay_s(1);

	}
}



//
//

