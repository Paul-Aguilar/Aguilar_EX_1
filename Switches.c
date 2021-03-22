/*
 * Switches.c
 *
 *  Created on: 17 feb. 2021
 *      Author: paula
/**
 * \file		Switches.c
 * \brief
 * 		Source file for the Switches (SW2 and SW3) device driver for Kinetis K64.
 * 		This is the application programming interface (API) for the Switches.
 * 		It contains the definition of the special variables and functions
 * 		for the configuration of the Switches.
 *  \date:		17 feb. 2021
 *  \author:	Fernanda Galeana & Paul Aguilar.
 */
#include "MK64F12.h"
#include "Switches.h"
#include "GPIO.h"
#include <Bits.h>

/**Value for the PCR to configure as GPIO with pull-up enable*/
gpio_pin_control_register_t pcr_sw_pullup = GPIO_MUX1 | GPIO_PE | GPIO_PS;


void SW2_config(void)
{
	/**Clock gating activation for GPIOC*/
	GPIO_clock_gating(GPIO_C);
	/**Pin control configuration of GPIOC pin6 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_C, SW2_bit, &pcr_sw_pullup);
	/**Configures pin6 of GPIOC as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT, SW2_bit);
}

void SW3_config(void)
{
	/**Clock gating activation for GPIOA*/
	GPIO_clock_gating(GPIO_A);
	/**Pin control configuration of GPIOA pin4 as GPIO with its pull-up resistor enabled*/
	GPIO_pin_control_register(GPIO_A, SW3_bit, &pcr_sw_pullup);
	/**Configures pin4 of GPIOA as input*/
	GPIO_data_direction_pin(GPIO_A,GPIO_INPUT, SW3_bit);
}

uint8_t sw_state(sw_name_t sw)
{
	uint8_t sw_value = 0;
	switch(sw)
		{
			case(SW2):
				sw_value = GPIO_read_pin(GPIO_C, SW2_bit);
				break;
			case(SW3):
				sw_value = GPIO_read_pin(GPIO_A, SW3_bit);
				break;
			default:
				return(FALSE);
		}//end switch
	return(sw_value);
}//end function






