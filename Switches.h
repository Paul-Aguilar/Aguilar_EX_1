
/**
 * \file		Switches.h
 * \brief
 * 		Source file for the Switches (SW2 and SW3) device driver for Kinetis K64.
 * 		This is the application programming interface (API) for the Switches.
 * 		It contains the definition of the special variables and functions
 * 		for the configuration of the Switches.
 *  \date:		17 feb. 2021
 *  \author:	Fernanda Galeana & Paul Aguilar.
 */

#ifndef SWITCHES_H_
#define SWITCHES_H_

#include <GPIO.h>
#include "Bits.h"

#define SW2_bit bit_6
#define SW3_bit bit_4


typedef enum{SW2,
			 SW3
			} sw_name_t;
/*
 	 \brief
 	 	 This function configures the GPIO needed for the SW2 with its pull-up resistor enabled.
 	 \param[in] void.
 	 \return void.
*/
void SW2_config(void);
/*
 	 \brief
 	 	 This function configures the GPIO needed for the SW3 with its pull-up resistor enabled.
 	 \param[in] void.
 	 \return void.
*/
void SW3_config(void);
/*
 	 \brief
 	 	 This function reads the state (input) from the corresponding switch.
 	 \param[in] sw The number of the switch to read.
 	 \return 1 if the switch is not pressed, 0 if it is pressed.
*/
uint8_t sw_state(sw_name_t sw);

#endif /* SWITCHES_H_ */
