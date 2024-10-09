/*
 * MSTP.c
 *
 *  Created on: Oct 9, 2024
 *      Author: kunal
 */

#include "MSTP.h"

static void Decode_MSTP_Packet(MSTP_Frame_Typedef *frame, uint8_t incoming_frame[])
{
    frame ->  preamble[0] = incoming_frame[0];
    frame ->  preamble[1] = incoming_frame[1];
    frame -> frame_type = incoming_frame[2];
    frame -> Destination_Address = incoming_frame[3];
    frame -> Source_Address = incoming_frame[4];
    frame -> Data_Length[0] = incoming_frame[5];
    frame -> Data_Length[1] = incoming_frame[6];
    frame -> Header_CRC = incoming_frame[7];

    int length = (frame -> Data_Length[0]<<8)|frame -> Data_Length[1];

    for(int i = 0; i < length; i++)
    {
        frame->Payload[i] = incoming_frame[8+i];
    }

    frame ->Footer_CRC[0] = 0xff;
    frame ->Footer_CRC[1] = 0xff;

}

static void Print_Packet(MSTP_Frame_Typedef *frame)
{
	Log_Print("Frame Type = %d\n",frame->frame_type);
	Log_Print("Destination_Address = %d\n",frame->Destination_Address);
	Log_Print("Source Address = %d\n",frame->Source_Address);
    uint16_t length =(frame->Data_Length[0] << 8) | (frame->Data_Length[1]);
    Log_Print("Data Length = %d\n", length);
    for(int i = 0; i < length; i++)
    {
    	Log_Print("%d,",frame->Payload[i]);
    }
    Log_Print("\n");
}

static uint8_t Calculate_MSTP_CRC(MSTP_Frame_Typedef *frame)
{
    uint16_t header[4];
    header[0] = frame->frame_type;
    header[1] = frame->Destination_Address;
    header[2] = frame->Source_Address;
    header[3] = frame->Data_Length[0] << 8 | frame->Data_Length[1];
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < 4; i++) {
        crc ^= header[i];
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

static bool Write_Packet(MSTP_Frame_Typedef *frame, uint8_t buffer[], uint16_t length)
{
	bool retval = 0;

	retval = 1;
	return retval;

}

static bool Get_Packet(MSTP_Frame_Typedef *frame, uint8_t buffer[])
{
	Log_Print("**************************************** \n");
	bool retval = 0;
	Decode_MSTP_Packet(frame,buffer);

	uint8_t temp_crc = Calculate_MSTP_CRC(frame);

	if(temp_crc ==  frame->Header_CRC)
	{
		Log_Print("Correct CRC \n");

		if(frame->Destination_Address == MY_ADDRESS)
		{
			Log_Print("Frame for me \n");
			Print_Packet(frame);
		}
		else
		{
			Log_Print("Frame not for me\n");
			retval = 0;
			return retval;
		}
	}
	else
	{
		Log_Print("Incorrect CRC \n");
	}

	return retval;
}

const MSTP_Driver_Typedef MSTP_Driver = {

		.get_packet = &Get_Packet,
		.write_packet = &Write_Packet,

};

