/*
 * SDIO_Defs.h
 *
 *  Created on: Oct 12, 2024
 *      Author: kunal
 */

#ifndef SDIO_SDIO_DEFS_H_
#define SDIO_SDIO_DEFS_H_

#include "main.h"


typedef struct SDIO_Mode{

	uint8_t SD1_or_MMC1;
	uint8_t SD4_or_MMC4;
	uint8_t MMC8;
}SDIO_Mode;


static const struct SDIO_Configurations{

	SDIO_Mode Mode;

}SDIO_Configurations = {

		.Mode = {
				.SD1_or_MMC1 = 1 << 0,
				.SD4_or_MMC4 = 1 << 1,
				.MMC8 = 1 << 2,
				},


};

#endif /* SDIO_SDIO_DEFS_H_ */
