/*
 * MSTP.h
 *
 *  Created on: Oct 9, 2024
 *      Author: kunal
 */

#ifndef BACNET_MSTP_MSTP_H_
#define BACNET_MSTP_MSTP_H_

#include "main.h"

#define Physical_Layer_As_IP 0
#define Physical_Layer_AS_RS232 1

#define MY_ADDRESS 0x03

#define APDU_Length 1497

#define MAX_FRAME_COUNT 20

typedef struct MSTP_Frame_Typedef
{
    uint8_t preamble[2];
    uint8_t frame_type;
    uint8_t Destination_Address;
    uint8_t Source_Address;
    uint8_t Data_Length[2];
    uint8_t Header_CRC;
    uint8_t Payload[APDU_Length];
    uint8_t Footer_CRC[2];

}MSTP_Frame_Typedef;

MSTP_Frame_Typedef MSTP_Frame_Stack[MAX_FRAME_COUNT];



typedef struct
{
	bool (*write_packet)(MSTP_Frame_Typedef *frame, uint8_t buffer[], uint16_t length);
	bool (*get_packet)(MSTP_Frame_Typedef *frame, uint8_t buffer[]);
}MSTP_Driver_Typedef;


extern const MSTP_Driver_Typedef MSTP_Driver;




#endif /* BACNET_MSTP_MSTP_H_ */
