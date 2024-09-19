#include "main.h"
#include "math.h"
#include "Console/Console.h"
#include "ADC/ADC.h"
#include "R454B/R454B.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"

DMA_Config Stepper_Motor;


#define array_length 2001
uint32_t data_array[array_length];

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
float Get_Saturation_Temp_From_Pressure(int pressure, PressureTempEntry *saturation_table, int TABLE_SIZE);
void Init_Stepper_Motor(void);
void Set_Stepper_Motor_Position(float control_signal);


uint16_t sensor_buffer[2];

ADC_Config sensor_config;



void TIM6_DAC_IRQHandler(void)
{
	TIM6 -> SR &= ~TIM_SR_UIF;

	Get_Temperature(sensor_buffer[0]);
	Get_Pressure(sensor_buffer[1]);

	float saturation_temp = Get_Saturation_Temp_From_Pressure(pressure, R454B_Saturation_Table, R545B_Table_Size);

	float superheat = temp_kelvin - saturation_temp;





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
//	Console_Init(9600); //921600

	for(int i = 0; i < array_length; i++)
	{
		data_array[i] = 0;
	}

	Init_Stepper_Motor();






	for(;;)
	{

		Set_Stepper_Motor_Position(10);
		Delay_s(1);
		Set_Stepper_Motor_Position(100);
		Delay_s(1);
		Set_Stepper_Motor_Position(1000);
		Delay_s(1);



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


float Get_Saturation_Temp_From_Pressure(int pressure, PressureTempEntry *saturation_table, int TABLE_SIZE)
{
	// Handle edge cases: pressure below the range
	if (pressure <= saturation_table[0].pressure) {
		return saturation_table[0].temp_avg;
	}
	// Handle edge cases: pressure above the range
	else if (pressure >= saturation_table[TABLE_SIZE - 1].pressure) {
		return saturation_table[TABLE_SIZE - 1].temp_avg;
	}

    // Search for the correct interval in the table
    for (int i = 0; i < TABLE_SIZE - 1; i++) {
        if (pressure >= saturation_table[i].pressure && pressure <= saturation_table[i + 1].pressure) {
            // Perform linear interpolation
            int pressure_low = saturation_table[i].pressure;
            int pressure_high = saturation_table[i + 1].pressure;
            float temp_low = saturation_table[i].temp_avg;
            float temp_high = saturation_table[i + 1].temp_avg;

            // Linear interpolation formula
            float saturation_temp = temp_low + (pressure - pressure_low) * (temp_high - temp_low) / (float)(pressure_high - pressure_low);
            return saturation_temp;
        }
    }

    // If not found, return an error value (should not reach here if data is properly bounded)
    return -999.9;
}



void Init_Stepper_Motor(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Enable TIM5 clock
	GPIO_Pin_Init(GPIOD, 12, GPIO_Configuration.Mode.Alternate_Function, GPIO_Configuration.Output_Type.Push_Pull, GPIO_Configuration.Speed.Very_High_Speed, GPIO_Configuration.Pull.No_Pull_Up_Down, GPIO_Configuration.Alternate_Functions.TIM_4);

    TIM4 -> CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
    TIM4 -> CCMR1 |= TIM_CCMR1_OC1PE;
    TIM4 -> CCER |= TIM_CCER_CC1E;
//    TIM4 -> EGR |= TIM_EGR_UG;
    TIM4 -> DIER |= TIM_DIER_CC1DE;
    TIM4->PSC = 84000000/(100*2000);                   // Prescaler
    TIM4->ARR = 100;                                   // Auto-reload value (period)
//    TIM4 -> CR1 |= TIM_CR1_CEN;
}



void Set_Stepper_Motor_Position(float control_signal)
{
	for(int i = 0; i < array_length; i++)
	{
		data_array[i] = 0;
	}

	Stepper_Motor.Request = DMA_Configuration.Request.TIM4_CH1;
	Stepper_Motor.circular_mode = DMA_Configuration.Circular_Mode.Disable;
	Stepper_Motor.flow_control = DMA_Configuration.Flow_Control.DMA_Control;
	Stepper_Motor.interrupts = DMA_Configuration.DMA_Interrupts.Transfer_Complete;
	Stepper_Motor.priority_level = DMA_Configuration.Priority_Level.Very_high;
	Stepper_Motor.transfer_direction = DMA_Configuration.Transfer_Direction.Memory_to_peripheral;

	Stepper_Motor.memory_data_size = DMA_Configuration.Memory_Data_Size.word;
	Stepper_Motor.memory_pointer_increment = DMA_Configuration.Memory_Pointer_Increment.Enable;

	Stepper_Motor.peripheral_pointer_increment = DMA_Configuration.Peripheral_Pointer_Increment.Disable;
	Stepper_Motor.peripheral_data_size = DMA_Configuration.Peripheral_Data_Size.word;

	DMA_Init(&Stepper_Motor);

	for(int i =0 ; i < (uint32_t)control_signal; i++)
	{
		data_array[i]= 50;
	}

	Stepper_Motor.memory_address = (uint32_t)&(data_array[0]);
	Stepper_Motor.peripheral_address = (uint32_t)&(TIM4->CCR1);
	Stepper_Motor.buffer_length = control_signal+1;
	DMA_Set_Target(&Stepper_Motor);
	DMA_Set_Trigger(&Stepper_Motor);

	TIM4 -> CR1 |= TIM_CR1_CEN;

	while(TIM4_CH1_DMA_Flag.Transfer_Complete_Flag != true){}


//	TIM4 -> CR1 &= ~TIM_CR1_CEN;

	DMA_Reset_Flags(TIM4_CH1_DMA_Flag);

}



void Sensor_Init(void)
{
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
}

