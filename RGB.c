
/**
 * \file		RGB.c
 * \brief
 * 		Source file for the LED RGB device driver for Kinetis K64.
 * 		This is the application programming interface (API) for the LED RGB.
 * 		It contains the definition of the special variables and functions
 * 		for the configuration of the LED RGB.
 *  \date:		16 feb. 2021
 *  \author:	Fernanda Galeana & Paul Aguilar.
 */

#include "MK64F12.h"
#include "RGB.h"
#include "GPIO.h"
#include "Bits.h"

gpio_pin_control_register_t pcr_gpiob_blue_led = GPIO_MUX1;
gpio_pin_control_register_t pcr_gpiob_red_led = GPIO_MUX1;
gpio_pin_control_register_t pcr_gpiob_green_led = GPIO_MUX1;
/*
 * Functions to initialize each primary color. They are only used inside the other
 * functions on this source file to avoid code repetition.
 */
uint8_t initialize_red(void)
{
	/**Clock gating activation for GPIOB*/
	GPIO_clock_gating(GPIO_B);
	/**Pin control configuration of GPIOB pin22 as GPIO*/
	GPIO_pin_control_register(GPIO_B,bit_22,&pcr_gpiob_red_led);
	/**Assignation of a safe value to the GPIOB pin22*/
	GPIO_set_pin(GPIO_B,bit_22);
	/**Configuration of GPIOB pin22 as output*/
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,bit_22);
	return(TRUE);
}//end function
uint8_t initialize_green(void)
{
	/**Clock gating activation for GPIOE*/
	GPIO_clock_gating(GPIO_E);
	/**Pin control configuration of GPIOE pin26 as GPIO*/
	GPIO_pin_control_register(GPIO_E,bit_26,&pcr_gpiob_green_led);
	/**Assignation of a safe value to the GPIOE pin26*/
	GPIO_set_pin(GPIO_E,bit_26);
	/**Configuration of GPIOE pin26 as output*/
	GPIO_data_direction_pin(GPIO_E,GPIO_OUTPUT,bit_26);
	return(TRUE);
}//end function
uint8_t initialize_blue(void)
{
	/**Clock gating activation for GPIOB*/
	GPIO_clock_gating(GPIO_B);
	/**Pin control configuration of GPIOB pin21 as GPIO*/
	GPIO_pin_control_register(GPIO_B,bit_21,&pcr_gpiob_blue_led);
	/**Assignation of a safe value to the GPIOB pin21*/
	GPIO_set_pin(GPIO_B,bit_21);
	/**Configuration of GPIOB pin21 as output*/
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,bit_21);
	return(TRUE);
}//end function


uint8_t RGB_initialize_all_colors(void)
{
	initialize_red();		/**Red configuration*/
	initialize_green();		/**Green configuration*/
	initialize_blue();		/**Blue configuration*/
	return(TRUE);
}//end function


uint8_t RGB_initialize_one_color(rgb_led_color_t color_name)
{
	switch(color_name)
				{
					case RGB_RED:		/** Color red is selected*/
						initialize_red();
						break;
					case RGB_GREEN:		/** Color green is selected*/
						initialize_green();
						break;
					case RGB_BLUE:		/** Color blue is selected*/
						initialize_blue();
						break;
					case RGB_PURPLE:	/** Color purple is selected*/
						initialize_red();
						initialize_blue();
						break;
					case RGB_YELLOW: 	/** Color yellow is selected*/
						initialize_red();
						initialize_green();
						break;
					case RGB_CYAN: 		/** Color cyan is selected*/
						initialize_green();
						initialize_blue();
						break;
					case RGB_WHITE: 	/** Color white is selected*/
						RGB_initialize_all_colors();
						break;
					default:/**If the option doesn't exist*/
						return(FALSE);
				}//end switch
	return(TRUE);
}//end function


uint8_t RGB_color_on(rgb_led_color_t color_name)
{
	switch(color_name)
				{
					case RGB_RED:		/** Color red is selected*/
						GPIO_set_pin(GPIO_E, bit_26);
						GPIO_set_pin(GPIO_B, bit_21);
						GPIO_clear_pin(GPIO_B, bit_22);
						break;
					case RGB_GREEN:		/** Color green is selected*/
						GPIO_set_pin(GPIO_B, bit_21);
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_clear_pin(GPIO_E, bit_26);
						break;
					case RGB_BLUE:		/** Color blue is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_set_pin(GPIO_E, bit_26);
						GPIO_clear_pin(GPIO_B, bit_21);
						break;
					case RGB_PURPLE:	/** Color purple is selected*/
						GPIO_set_pin(GPIO_E, bit_26);
						GPIO_clear_pin(GPIO_B, bit_22);
						GPIO_clear_pin(GPIO_B, bit_21);
						break;
					case RGB_YELLOW: 	/** Color yellow is selected*/
						GPIO_set_pin(GPIO_B, bit_21);
						GPIO_clear_pin(GPIO_B, bit_22);
						GPIO_clear_pin(GPIO_E, bit_26);
						break;
					case RGB_CYAN: 		/** Color cyan is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_clear_pin(GPIO_E, bit_26);
						GPIO_clear_pin(GPIO_B, bit_21);
						break;
					case RGB_WHITE: 	/** Color white is selected*/
						GPIO_clear_pin(GPIO_B, bit_22);
						GPIO_clear_pin(GPIO_B, bit_21);
						GPIO_clear_pin(GPIO_E, bit_26);
						break;
					default:/**If the option doesn't exist*/
						return(FALSE);
				}//end switch
		return(TRUE);
}//end function


uint8_t RGB_color_off(rgb_led_color_t color_name)
{
	switch(color_name)
				{
					case RGB_RED:		/** Color red is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						break;
					case RGB_GREEN:		/** Color green is selected*/
						GPIO_set_pin(GPIO_E, bit_26);
						break;
					case RGB_BLUE:		/** Color blue is selected*/
						GPIO_set_pin(GPIO_B, bit_21);
						break;
					case RGB_PURPLE:	/** Color purple is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_set_pin(GPIO_B, bit_21);
						break;
					case RGB_YELLOW: 	/** Color yellow is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_set_pin(GPIO_E, bit_26);
						break;
					case RGB_CYAN: 		/** Color cyan is selected*/
						GPIO_set_pin(GPIO_E, bit_26);
						GPIO_set_pin(GPIO_B, bit_21);
						break;
					case RGB_WHITE: 	/** Color white is selected*/
						GPIO_set_pin(GPIO_B, bit_22);
						GPIO_set_pin(GPIO_B, bit_21);
						GPIO_set_pin(GPIO_E, bit_26);
						break;
					default:/**If the option doesn't exist*/
						return(FALSE);
				}//end switch
	return(TRUE);

}//end function
