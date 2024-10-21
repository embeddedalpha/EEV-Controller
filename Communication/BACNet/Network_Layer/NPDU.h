/*
 * NPDU.h
 *
 *  Created on: Oct 9, 2024
 *      Author: kunal
 */

#ifndef BACNET_NETWORK_LAYER_NPDU_H_
#define BACNET_NETWORK_LAYER_NPDU_H_

#include "main.h"
#include "BACNet/Application_Layer/APDU.h"


static const struct NPDU_Control{

	/*
	 * 1: Indicates that the packet contains a network layer message (like a broadcast or routing message).
	 * 0: Indicates that the packet only contains an APDU (application layer message).
	 */
	struct Network_Layer_Message_Flag{
		uint8_t Mask;
		uint8_t Contains_Network_Layer_Message;
		uint8_t Contains_APDU;
	}Network_Layer_Message_Flag;

	/*
	 * 1: The destination network address is present.
	 * 0: The destination address is not present.
	 */
	struct Destination_Specified_Flag
	{
		uint8_t Mask;
		uint8_t Destination_Network_Address_Present;
		uint8_t Destination_Network_Address_Not_Present;
	}Destination_Specified_Flag;

	/*
	 * 1: The source network address is present.
	 * 0: The source address is not present.
	 */
	struct Source_Specified_Flag
	{
		uint8_t Mask;
		uint8_t Source_Network_Address_Present;
		uint8_t Source_Network_Address_Not_Present;
	}Source_Specified_Flag;

	/*
	 * 1: The sender expects a reply to the message.
	 * 0: No reply is expected.
	 */
	struct Expected_Reply_Flag
	{
		uint8_t Mask;
		uint8_t Expected_Reply;
		uint8_t No_Reply;
	}Expected_Reply_Flag;

	struct Priority_Flag{
		/*
		 * These are critical messages, such as fire alarm signals or emergency shutdown commands.
		 * They take precedence over all other traffic in the network.
		 */

		uint8_t Life_Safety_Message;

		/*
		 * Messages related to urgent but non-life-threatening operations
		 */

		uint8_t Urgent_Operation;

		/*
		 * Messages for controlling essential equipment (e.g., HVAC systems, security systems).
		 */
		uint8_t Critical_Equipment;

		/*
		 * General traffic for typical building operations.
		 * Most regular control messages, such as adjusting temperature setpoints or turning lights on/off,
		 * use this priority.
		 */
		uint8_t Normal_Operation;

	}Priority_Flag;

}NPDU_Control = {
		.Network_Layer_Message_Flag = {
				.Mask = 1 << 7,
				.Contains_Network_Layer_Message = 1 << 7,
				.Contains_APDU = 0 << 7,
		},

		.Destination_Specified_Flag = {
				.Mask = 1 << 5,
				.Destination_Network_Address_Present = 1<<5,
				.Destination_Network_Address_Not_Present = 0 << 5,
		},

		.Source_Specified_Flag = {
				.Mask = 1 << 4,
				.Source_Network_Address_Present = 1 << 4,
				.Source_Network_Address_Not_Present = 1<< 4,
		},

		.Expected_Reply_Flag = {
				.Mask =  1 << 3,
				.Expected_Reply = 1 << 3,
				.No_Reply = 0 << 3,
		},

		.Priority_Flag = {
				.Life_Safety_Message = 0b000,
				.Urgent_Operation = 0b001,
				.Critical_Equipment = 0b010,
				.Normal_Operation = 0b011,
		},

}
;

typedef struct NPDU_Frame_Format{

	uint8_t Version;
	uint8_t Control;
	uint8_t DNET[2];
	uint8_t DLEN;
	uint8_t DADR[6];
	uint8_t SNET;
	uint8_t SLEN;
	uint8_t SADR[6];
	uint8_t HOP_Count;
	uint8_t Message_Type;
	uint8_t Vendor_ID[2];
	uint8_t APDU[APDU_MAX];

}NPDU_Frame_Format;


void BACNet_Construct_NPDU_Frame(NPDU_Frame_Format *frame, uint8_t *buffer, uint16_t length);


#endif /* BACNET_NETWORK_LAYER_NPDU_H_ */
