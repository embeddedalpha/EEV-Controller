/*
 * Stepper_Motor.h
 *
 *  Created on: Sep 21, 2024
 *      Author: kunal
 */

#ifndef STEPPER_MOTOR_STEPPER_MOTOR_H_
#define STEPPER_MOTOR_STEPPER_MOTOR_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"


void Stepper_Motor_Init(void);
void Set_Stepper_Motor_Position(float control_signal, uint16_t speed);


#endif /* STEPPER_MOTOR_STEPPER_MOTOR_H_ */
