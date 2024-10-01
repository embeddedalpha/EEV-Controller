/*
 * Application.c
 *
 *  Created on: Sep 30, 2024
 *      Author: kunal
 */

#include "Application.h"

uint16_t sensor_buffer[2];

ADC_Config sensor_config;


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


