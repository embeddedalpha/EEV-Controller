/*
 * Application.c
 *
 *  Created on: Sep 30, 2024
 *      Author: kunal
 */

#include "Application.h"

uint16_t sensor_buffer[2];

ADC_Config sensor_config;

const int STEP_PER_DEGREE	= 10;
const int MAX_STEPS			= 2000;
const int MAX_SPEED			= 800;
const int MIN_SPEED			= 200;
const int RATE_LIMIT		= 50;


float temp_kelvin = 0.0;
float temp_celsius = 0.0;
float pressure = 0.0;

const float R_FIXED = 10000;  // Fixed resistor value in ohms (10kΩ)
const float BETA = 3950;      // Beta parameter for the thermistor
const float T0 = 298.15;      // Room temperature in Kelvin (25°C)
const float R0 = 10000 ;      // Resistance of the thermistor at T0 (10kΩ)
const float VIN = 3.3 ;       // Input voltage (e.g., 5V)
const int MAX_PRESSURE = 50;  // PSI


float Get_Temperature(void)
{
	float Vout = 0.0;
	float R_thermistor = 0.0;


	Vout = (sensor_buffer[0] / 1024.0)*VIN;
	R_thermistor = R_FIXED * (VIN / Vout - 1);

	temp_kelvin = 1 / ((1/T0) + (1/BETA) * log(R_thermistor/R0));
	temp_celsius = temp_kelvin - 273.15;

	return temp_celsius;
}

float Get_Pressure(void)
{
	return (pressure = (sensor_buffer[1] / 1024.0)*MAX_PRESSURE);
}


float Get_Superheat(float temp, float sat_temp)
{
	float superheat = temp - sat_temp;

	return superheat;
}

void Control_Stepper_Motor(float control_Signal)
{
	int steps_to_move = (int)(control_Signal * STEP_PER_DEGREE);

	if(steps_to_move > RATE_LIMIT) steps_to_move = RATE_LIMIT;
	if(steps_to_move < -RATE_LIMIT) steps_to_move = -RATE_LIMIT;

	if(steps_to_move > MAX_STEPS) steps_to_move = MAX_STEPS;
	if(steps_to_move < -MAX_STEPS) steps_to_move = -MAX_STEPS;

	int direction = (steps_to_move > 0) ? 1 : -1; // 1 for open and -1 for close

	int speed = MIN_SPEED + (abs(steps_to_move) * (MAX_SPEED - MIN_SPEED)/MAX_STEPS);

	if(speed > MAX_SPEED) speed = MAX_SPEED;

	Set_Stepper_Motor_Position(steps_to_move, speed, direction);
}
