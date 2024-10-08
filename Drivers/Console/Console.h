/*
 * Console.h
 *
 *  Created on: Dec 19, 2023
 *      Author: kunal
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "main.h"
#include "GPIO/GPIO.h"
#include "USART/USART.h"
#include "DMA/DMA.h"


void Console_Init(int32_t baudrate);
void printConsole(char *msg, ...);
int readConsole(const char *msg, ...);


#endif /* CONSOLE_H_ */
