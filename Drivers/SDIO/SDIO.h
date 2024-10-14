/*
 * SDIO.h
 *
 *  Created on: Oct 12, 2024
 *      Author: kunal
 */

#ifndef SDIO_SDIO_H_
#define SDIO_SDIO_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "DMA/DMA.h"
#include "SDIO_Defs.h"


typedef struct SDIO_Config
{
	uint8_t Mode;
}SDIO_Config;

int8_t SDIO_Init(SDIO_Config *config);
void SDIO_Power_Off(SDIO_Config *config);
void SDIO_Power_On(SDIO_Config *config);


#endif /* SDIO_SDIO_H_ */
