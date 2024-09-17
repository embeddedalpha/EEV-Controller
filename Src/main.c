#include "main.h"
#include "Console/Console.h"
#include "ADC/ADC.h"
#include "math.h"
#include "R454B/R454B.h"

float temp_kelvin = 0.0;
float temp_celsius = 0.0;
float pressure = 0.0;

const float R_FIXED = 10000;  // Fixed resistor value in ohms (10kΩ)
const float BETA = 3950;      // Beta parameter for the thermistor
const float T0 = 298.15;      // Room temperature in Kelvin (25°C)
const float R0 = 10000 ;      // Resistance of the thermistor at T0 (10kΩ)
const float VIN = 3.3 ;       // Input voltage (e.g., 5V)
const int MAX_PRESSURE = 50;  // PSI

void Get_Temperature(uint16_t adc_value);
void Get_Pressure(uint16_t adc_value);

uint16_t sensor_buffer[2];

ADC_Config sensor_config;



void TIM6_DAC_IRQHandler(void)
{
	TIM6 -> SR &= ~TIM_SR_UIF;

	Get_Temperature(sensor_buffer[0]);



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
	Console_Init(9600); //921600
	General_Timer_Update_Init();


	sensor_config.Channel_0.Enable = ADC_Configuration.Channel.Enable.Enable;
	sensor_config.Channel_0.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
	sensor_config.Channel_0.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_1;

	sensor_config.Channel_1.Enable = ADC_Configuration.Channel.Enable.Enable;
	sensor_config.Channel_1.Sample_Time = ADC_Configuration.Channel.Sample_Time._3_Cycles;
	sensor_config.Channel_1.Sequence_Number = ADC_Configuration.Channel.Sequence_Number.Sequence_2;

	sensor_config.Port = ADC_Configuration.Port._ADC1_;
	sensor_config.Channel_Type = ADC_Configuration.Channel_Type.Regular;
	sensor_config.Conversion_Mode = ADC_Configuration.Conversion_Mode.Single;
	sensor_config.Data_Alignment = ADC_Configuration.Data_Alignment.Left_Justified;
	sensor_config.Resolution = ADC_Configuration.Resolution.Bit_12;
	sensor_config.Watchdog_Analog.Enable = ADC_Configuration._Watchdog_Analog_.Disable;
	sensor_config.External_Trigger.Enable = ADC_Configuration.Regular_External_Trigger_Enable.Trigger_On_Rising_Edge;
	sensor_config.External_Trigger.Sampling_Frequency = 100;
	sensor_config.External_Trigger.Trigger_Event = ADC_Configuration.Regular_External_Trigger_Event.Timer_2_CC2;

	ADC_Init(&sensor_config);
	ADC_Start_Capture(&sensor_config, &sensor_buffer[0]);



	for(;;)
	{



	}
}


void Get_Temperature(uint16_t adc_value)
{
	float Vout = 0.0;
	float R_thermistor = 0.0;


	Vout = (adc_value / 1024.0)*VIN;
	R_thermistor = R_FIXED * (VIN / Vout - 1);

	temp_kelvin = 1 / ((1/T0) + (1/BETA) * log(R_thermistor/R0));
	temp_celsius = temp_kelvin - 273.15;
}

void Get_Pressure(uint16_t adc_value)
{
	pressure = (adc_value / 1024.0)*MAX_PRESSURE;
}

void Get_Saturation_Temp_From_Pressure()
{

}
