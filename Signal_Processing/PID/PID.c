/*
 * PID.c
 *
 *  Created on: Sep 17, 2024
 *      Author: kunal
 */

#include "../../Signal_Processing/PID/PID.h"


void  PID_Controller_Init(PID_Controller_Typedef *pid_instance)
{
	pid_instance -> integrator = 0.0f;
	pid_instance -> prev_Error = 0.0f;
	pid_instance -> differentiator = 0.0f;
	pid_instance -> prev_Measurement = 0.0f;
	pid_instance -> out = 0.0f;
}



float PID_Controller_Update(PID_Controller_Typedef *pid_instance, float measurement)
{
	float error = pid_instance -> setpoint - measurement;

	float proportional = pid_instance -> Kp * error;

	pid_instance -> integrator = pid_instance -> integrator +
			                     ((pid_instance -> Ki * pid_instance -> T_Sampling_Time * 0.5f)*(error - pid_instance->prev_Error));


	float Integrator_Limit_Min = 0.0f;
	float Integrator_Limit_Max = 0.0f;

	if(pid_instance -> Limit_Max > proportional)
	{
		Integrator_Limit_Max = pid_instance -> Limit_Max - proportional;
	}else{
		Integrator_Limit_Max = 0.0f;
	}

	if(pid_instance -> Limit_Min < proportional)
	{
		Integrator_Limit_Min = pid_instance -> Limit_Min - proportional;
	}else{
		Integrator_Limit_Min = 0.0f;
	}

	if(pid_instance -> integrator > Integrator_Limit_Max)
	{
		pid_instance -> integrator = Integrator_Limit_Max;
	}
	else if(pid_instance ->integrator < Integrator_Limit_Min)
	{
		pid_instance -> integrator = Integrator_Limit_Min;
	}


	pid_instance -> differentiator = ((2.0f * pid_instance -> Kd *(error - pid_instance -> prev_Error))  + ((2.0f * pid_instance -> tau - pid_instance->T_Sampling_Time)*pid_instance -> differentiator) )/
			                         (2.0f * pid_instance -> tau + pid_instance -> T_Sampling_Time);

	pid_instance -> out = proportional + pid_instance -> integrator + pid_instance -> differentiator;

	if(pid_instance -> out > pid_instance -> Limit_Max)
	{
		pid_instance -> out = pid_instance -> Limit_Max;
	}
	else if(pid_instance -> out < pid_instance -> Limit_Min)
	{
		pid_instance -> out = pid_instance -> Limit_Min;
	}

	pid_instance -> prev_Error = error;
	pid_instance -> prev_Measurement = measurement;

	return pid_instance -> out;
}
