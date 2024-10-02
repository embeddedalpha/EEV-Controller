/*
 * Application.h
 *
 *  Created on: Sep 30, 2024
 *      Author: kunal
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "math.h"
#include "Console/Console.h"
#include "ADC/ADC.h"


float Get_Temperature(void);
float Get_Pressure(void);
float Get_Superheat(float temp, float sat_temp);
void Control_Stepper_Motor(float control_Signal);

#endif /* APPLICATION_H_ */
