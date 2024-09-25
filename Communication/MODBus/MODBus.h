/*
 * MODBus.h
 *
 *  Created on: Sep 19, 2024
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_H_
#define MODBUS_MODBUS_H_

#include "main.h"
#include "USART/USART.h"
#include "MODBus_Defs.h"

#define turnaround_delay_ms 100
#define response_time_out_ms 1000

typedef struct ModBus_Request{

	uint8_t slave_address;
	uint8_t function_code;
	uint8_t starting_address;
	uint8_t quantity;
	uint16_t crc;
}ModBus_Request;

typedef struct ModBus_Frame{

    uint8_t slaveAddress;
    uint8_t functionCode;
    uint16_t registerAddress;
    uint16_t numberOfRegisters;
    uint8_t requestData[256];  // Buffer to hold incoming request data
    uint8_t responseData[256]; // Buffer to hold outgoing response data
    uint16_t crc;              // CRC for RTU mode
}ModBus_Frame;

typedef struct ModBus_Config{

	uint8_t slave_address;
	uint8_t type;
	uint32_t buadrate;

}Modbus_Config;



unsigned short ModBus_CRC16(uint16_t *packet, uint16_t len);

int8_t Modbus_Init(Modbus_Config *config);



#endif /* MODBUS_MODBUS_H_ */
