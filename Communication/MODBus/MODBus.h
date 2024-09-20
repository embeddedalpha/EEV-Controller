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


typedef struct Modbus_Request{

	uint8_t slave_address;
	uint8_t function_code;
	uint8_t starting_address;
	uint8_t quantity;
	uint16_t crc;
}Modbus_Request;

typedef struct Modbus_Response{

	uint8_t slave_address;
	uint8_t function_code;
	uint8_t byte_count;
	uint8_t data[256];
	uint16_t crc;
}Modbus_Response;

typedef struct Modbus_Config{



}Modbus_Config;


#endif /* MODBUS_MODBUS_H_ */
