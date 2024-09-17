/*
 * RTC.c
 *
 *  Created on: Aug 31, 2024
 *      Author: kunal
 */

#include "RTC.h"

  uint8_t Hour;
  uint8_t Minute;
  uint8_t Second;
  uint8_t Day;
 uint8_t Month;
 uint8_t Year;
uint8_t Day_of_Week;






static uint8_t BCD_to_Decimal(uint8_t bcd)
{
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}

static uint8_t Decimal_to_BCD(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

static void Enter_Initalization_Mode(void)
{
    // Unlock the RTC registers
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;
}

static void Exit_Initalization_Mode(void)
{
    // Lock the RTC registers
    RTC->WPR = 0xFF;
}


void RTC_Init(RTC_Config *config)
{




    // Enable the power interface clock
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    // Enable access to the backup domain
    PWR->CR |= PWR_CR_DBP;

    // Enable the LSE oscillator
    RCC->BDCR |= RCC_BDCR_LSEON;
    while (!(RCC->BDCR & RCC_BDCR_LSERDY)) {
        // Wait until LSE is ready
    }

    // Select the RTC clock source as LSE
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;

    // Enable the RTC clock
    RCC->BDCR |= RCC_BDCR_RTCEN;

    // Disable write protection for RTC registers
    RTC->WPR = 0xCA;
    RTC->WPR = 0x53;

    // Enter initialization mode
    RTC->ISR |= RTC_ISR_INIT;
    while (!(RTC->ISR & RTC_ISR_INITF));  // Wait for initialization mode

//    // Configure the wake-up timer
//    RTC->CR &= ~RTC_CR_WUTE; // Disable the wake-up timer to modify settings
//    while (!(RTC->ISR & RTC_ISR_WUTWF));  // Wait until WUTWF is set

//    RTC->WUTR = 0x0000FFFF;  // Set the wake-up timer auto-reload value (example value)
//    RTC->CR |= RTC_CR_WUTE | RTC_CR_WUTIE;  // Enable wake-up timer and wake-up interrupt
    RTC->CR |= RTC_CR_TSE | RTC_CR_TSIE;  // Enable wake-up timer and wake-up interrupt

    uint8_t hours_bcd = Decimal_to_BCD(config->Time_Setup.Hour);
    uint8_t minutes_bcd = Decimal_to_BCD(config->Time_Setup.Minute);
    uint8_t seconds_bcd = Decimal_to_BCD(config->Time_Setup.Second);

    // Set the time
    RTC->TR = (hours_bcd << 16) | (minutes_bcd << 8) | (seconds_bcd);

    uint8_t year = Decimal_to_BCD(config->Time_Setup.Year);
    uint8_t month = Decimal_to_BCD(config->Time_Setup.Month);
    uint8_t day = Decimal_to_BCD(config->Time_Setup.Day);
    uint8_t weekday = Decimal_to_BCD(config->Time_Setup.Weekday);

    // Set the date
    RTC -> DR = (year << 16) | (weekday << 13) | (month << 8) | (day << 0);

    // Exit initialization mode
    RTC->ISR &= ~RTC_ISR_INIT;

    // Enable write protection for RTC registers
    RTC->WPR = 0xFF;

    PWR -> CR &= ~PWR_CR_DBP;

	// Enable the clock for the SYSCFG peripheral (required for EXTI configuration)
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // Clear EXTI line 22 configuration
    EXTI->IMR |= EXTI_IMR_IM21;     // Unmask EXTI line 22 (Enable Interrupt)
    EXTI->RTSR |= EXTI_RTSR_TR21;   // Enable rising edge trigger for line 22
    NVIC_EnableIRQ(TAMP_STAMP_IRQn);  // Enable RTC Wake-up interrupt in NVIC
    NVIC_SetPriority(TAMP_STAMP_IRQn, 0); // Set the priority level for the interrupt


}

void RTC_Set_Alarm(RTC_Config *config)
{

	if(config->Alarm_1.Enable == ENABLE)
	{
		Enter_Initalization_Mode();

		Exit_Initalization_Mode();
//
	}
	if(config->Alarm_2.Enable == ENABLE)
	{
		Enter_Initalization_Mode();

		Exit_Initalization_Mode();
	}

}

void RTC_Get_Time(void) {

    // Read time from RTC in BCD format
    uint32_t time_bcd = RTC->TR;

    // Convert BCD to decimal
    Hour = BCD_to_Decimal((time_bcd >> 16) & 0xFF);
    Minute = BCD_to_Decimal((time_bcd >> 8) & 0xFF);
    Second = BCD_to_Decimal(time_bcd & 0xFF);
}

void RTC_Get_Date(void)
{
    // Read time from RTC in BCD format
    uint32_t year_bcd = RTC->DR;

    // Convert BCD to decimal
    Year = BCD_to_Decimal((year_bcd >> 16) & 0xFF);
    Month = BCD_to_Decimal((year_bcd >> 8) & 0xFF);
    Day = BCD_to_Decimal(year_bcd & 0xFF);
    Day_of_Week = BCD_to_Decimal((year_bcd >> 13) & 0xFF);
}
