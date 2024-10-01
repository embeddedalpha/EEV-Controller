/*
 * PID.h
 *
 *  Created on: Sep 17, 2024
 *      Author: kunal
 */

#ifndef PID_PID_H_
#define PID_PID_H_

#include "main.h"

typedef struct PID_Controller_Typedef{

	float setpoint;

	float Kp;
	float Ki;
	float Kd;

	float tau;

	float Limit_Min;
	float Limit_Max;

	float T_Sampling_Time;

	float integrator;
	float prev_Error;
	float differentiator;
	float prev_Measurement;

	float out;
}PID_Controller_Typedef;

void  PID_Controller_Init(PID_Controller_Typedef *pid_instance);
float PID_Controller_Update(PID_Controller_Typedef *pid_instance, float measurement);


#endif /* PID_PID_H_ */
