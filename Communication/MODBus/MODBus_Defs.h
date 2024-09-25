/*
 * MODBus_Defs.h
 *
 *  Created on: Sep 19, 2024
 *      Author: kunal
 */

#ifndef MODBUS_MODBUS_DEFS_H_
#define MODBUS_MODBUS_DEFS_H_

#include "main.h"

static const struct MODBus_Functions{

	uint8_t Read_Coil;
	uint8_t Read_Discrete_Inputs;
	uint8_t Read_Holding_Registers;
	uint8_t Read_Input_Registers;

	uint8_t Write_Single_Coil;
	uint8_t Write_Single_Register;
	uint8_t Write_Multiple_Coils;
	uint8_t Write_Multiple_Registers;

	uint8_t Read_Write_Mulitple_Registers;

}MODBus_Functions = {

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

static const struct MODBus_Exception_Code{

	uint8_t Illegal_Function;
	uint8_t Illegal_Data_Address;
	uint8_t Illegal_Data_Value;
	uint8_t Slave_Device_Failure;
	uint8_t Acknowledge;
	uint8_t Slave_Device_Busy;
	uint8_t Negative_Acknowledge;
	uint8_t Memory_Parity_Error;
	uint8_t Gateway_Path_Unavailable;
	uint8_t Gateway_Target_Device_Failed_to_Respond;


}MODBus_Exception_Code =
		{
				.Illegal_Function = 0x01,
				.Illegal_Data_Address = 0x02,
				.Illegal_Data_Value = 0x03,
				.Slave_Device_Failure = 0x04,
				.Acknowledge = 0x05,
				.Slave_Device_Busy = 0x06,
				.Negative_Acknowledge = 0x07,
				.Memory_Parity_Error = 0x08,
				.Gateway_Path_Unavailable = 0x0A,
				.Gateway_Target_Device_Failed_to_Respond = 0xB

		};




#endif /* MODBUS_MODBUS_DEFS_H_ */
