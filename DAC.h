/*
 * DAC.h
 *
 *  Created on: 15 mar. 2021
 *      Author: paula
 */


#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"
#include "MK64F12.h"

typedef enum
{
	DAC_0,
	DAC_1
}DAC_enum;

/*Configuration for DACx_C0*/
#define DACEN		0x80
#define DACRFS		0x40
#define DACTRGSEL	0x20
#define LPEN		0x08
#define DACBWIEN 	0x04
#define DACBTIEN 	0x02
#define DACBBIEN 	0x01

/*Configuration for DACx_C1*/
#define DMAEN			0x80
#define DACBFMD_NORMAL	0x00
#define DACBFMD_SWING	0x04
#define DACBFMD_OTS		0x08
#define DACBFEN			0x01



void DAC_config(DAC_enum dac_num, uint8_t DACx_C0, uint8_t DACx_C1);
void DAC_start(void);
void DAC_stop(void);
uint8_t DAC_get_status(DAC_enum dac_num);
void DAC_out_buffer(uint16_t signal_data);
void DAC_Buffer_interrupt(DAC_enum dac_num, uint8_t interrupt);
void DAC_clear(void);



#endif /* DAC_H_ */
