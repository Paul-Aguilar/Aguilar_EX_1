/*
 * DAC.c
 *
 *  Created on: 15 mar. 2021
 *      Author: paula
 */



#include "stdint.h"
#include "MK64F12.h"
#include "bits.h"
#include "DAC.h"

#define BUFFER_SHIFT 4U
#define SHIFT_DATLH 8U
#define MASK_DATLH 0x0F00U

void DAC_config(DAC_enum dac_enum, uint8_t DACx_C0, uint8_t DACx_C1)
{
	switch(dac_enum)
	{
	case DAC_0:
		SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
		DAC0->C0 |= DACx_C0;
		DAC0->C1 |= DACx_C1;
		break;
	case DAC_1:
		SIM->SCGC2 |= SIM_SCGC2_DAC1_MASK;
		DAC1->C0 |= DACx_C0;
		DAC1->C1 |= DACx_C1;
		break;
	}
}

void DAC_set_buffer(DAC_enum dac_enum, uint8_t BF_read_pointer, uint8_t BF_Upper_limit)
{
	BF_read_pointer <<= BUFFER_SHIFT;
	switch(dac_enum)
	{
	case DAC_0:
		DAC0->C2 = BF_read_pointer|BF_Upper_limit;
		break;
	case DAC_1:
		DAC1->C2 = BF_read_pointer|BF_Upper_limit;
		break;
	}
}

uint8_t DAC_get_status(DAC_enum dac_enum)
{
	uint8_t status = 0;

	switch(dac_enum)
	{
	case DAC_0:
		status = DAC0->SR;
		break;
	case DAC_1:
		status = DAC1->SR;
		break;
	}
	return(status);
}
void DAC_out_buffer(uint16_t signal_data)
{
		DAC0->DAT[0].DATL = (uint8_t)(signal_data);
		DAC0->DAT[0].DATH = (uint8_t)((signal_data & MASK_DATLH)>>SHIFT_DATLH);
}
void DAC_Buffer_interrupt(DAC_enum dac_enum, uint8_t interrupt)
{
	uint8_t dac_sw_trg;
	dac_sw_trg = interrupt << BUFFER_SHIFT;

	switch(dac_enum)
	{
	case DAC_0:
		DAC0->C0 |= dac_sw_trg;
		break;
	case DAC_1:
		DAC1->C0 |= dac_sw_trg;
		break;
	}
}
