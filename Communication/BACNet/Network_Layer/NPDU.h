/*
 * NPDU.h
 *
 *  Created on: Oct 9, 2024
 *      Author: kunal
 */

#ifndef BACNET_NETWORK_LAYER_NPDU_H_
#define BACNET_NETWORK_LAYER_NPDU_H_

typedef struct NPDU_Frame_Format{

	uint8_t Version;
	uint8_t Control;
	uint8_t DNET[2];
	uint8_t DLEN;
	uint8_t DADR[100];
	uint8_t SNET;
	uint8_t SLEN;
	uint8_t SADR[100];
	uint8_t HOP_Count;
	uint8_t Message_Type;
	uint8_t Vendor_ID[2];
	uint8_t APDU[APDU_Length];

}NPDU_Frame_Format;


#endif /* BACNET_NETWORK_LAYER_NPDU_H_ */
