/*
 * MODBus.h
 *
 *  Created on: Sep 19, 2024
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_H_
#define MODBUS_MODBUS_H_

#include "main.h"
#include "MODBus.h"

#define turnaround_delay_ms 100
#define response_time_out_ms 1000

typedef struct ModBus_Request{

	uint8_t slave_address;
	uint8_t function_code;
	uint8_t starting_address;
	uint8_t quantity;
	uint16_t crc;
}ModBus_Request;

typedef struct ModBus_Response{

	uint8_t slave_address;
	uint8_t function_code;
	uint8_t byte_count;
	uint8_t data[256];
	uint16_t crc;
}Modbus_Response;

typedef struct ModBus_Config{





}Modbus_Config;

unsigned short ModBus_CRC16(uint16_t *packet, uint16_t len);




#endif /* MODBUS_MODBUS_H_ */
