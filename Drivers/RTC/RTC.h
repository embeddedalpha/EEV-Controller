/*
 * RTC.h
 *
 *  Created on: Aug 31, 2024
 *      Author: kunal
 */

#ifndef RTC_H_
#define RTC_H_

#include "main.h"

extern  uint8_t Hour;
extern  uint8_t Minute;
extern  uint8_t Second;
extern  uint8_t Day;
extern  uint8_t Month;
extern  uint8_t Year;
extern  uint8_t Day_of_Week;


typedef struct RTC_Config
{
	uint8_t Format;

	struct Time_Setup
	{

		uint8_t Second;
		uint8_t Minute;
		uint8_t Hour;


		uint16_t Year;
		uint8_t Month;
		uint8_t Day;
		uint8_t Weekday;
	}Time_Setup;

	struct RTC_Interrupts{
		bool Time_Stamp_Enable;
		bool Wake_up_Timer_Enable;
		bool Alarm_A_Enable;
		bool Alarm_B_Enable;
	}RTC_Interrupts;

	struct Alarm_1
	{
		bool Enable;
		uint8_t Day;
		uint8_t Second;
		uint8_t Minute;
		uint8_t Hour;
		bool Output_Pulse_Enable;
	}Alarm_1;

	struct Alarm_2
	{
		bool Enable;
		uint8_t Day;
		uint8_t Second;
		uint8_t Minute;
		uint8_t Hour;
		bool Output_Pulse_Enable;
	}Alarm_2;

}RTC_Config;

void RTC_Init(RTC_Config *config);
void RTC_Set_Alarm(RTC_Config *config);
void RTC_Get_Date(void);
void RTC_Get_Time(void);

#endif /* RTC_H_ */
