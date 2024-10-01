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
#include "R454B.h"
#include "PID/PID.h"



float Get_Temperature(void);
float Get_Pressure(void);

float Get_Saturation_Temp_From_Pressure(int pressure, PressureTempEntry *saturation_table, int TABLE_SIZE);



#endif /* APPLICATION_H_ */
