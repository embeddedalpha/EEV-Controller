/*
 * MODBus_Defs.h
 *
 *  Created on: Sep 19, 2024
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_DEFS_H_
#define MODBUS_MODBUS_DEFS_H_

#include "main.h"

static const struct MODBus_Function_Field{

	uint8_t Read_Coil;
	uint8_t Read_Discrete_Inputs;
	uint8_t Read_Holding_Registers;
	uint8_t Read_Input_Registers;

	uint8_t Write_Single_Coil;
	uint8_t Write_Single_Register;
	uint8_t Write_Multiple_Coils;
	uint8_t Write_Multiple_Registers;

	uint8_t Read_Write_Mulitple_Registers;

}MODBus_Function_Field = {

		.Read_Coil              = 0x01,
		.Read_Discrete_Inputs   = 0x02,
		.Read_Holding_Registers = 0x03,
		.Read_Input_Registers   = 0x04,
		.Write_Single_Coil      = 0x05,
		.Write_Single_Register  = 0x06,
		.Write_Multiple_Coils   = 0x0f,
		.Write_Multiple_Registers = 0x10,
		.Read_Write_Mulitple_Registers = 0x17,
};


#endif /* MODBUS_MODBUS_DEFS_H_ */
