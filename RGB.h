/**
 * \file		RGB.h
 * \brief
 * 		Source file for the LED RGB device driver for Kinetis K64.
 * 		This is the application programming interface (API) for the LED RGB.
 * 		It contains the definition of the special variables and functions
 * 		for the configuration of the LED RGB.
 *  \date:		16 feb. 2021
 *  \author:	Fernanda Galeana & Paul Aguilar.
 */

#ifndef RGB_H_
#define RGB_H_

#include "stdint.h"


/* Definition of the constants to select an specific from the different combinations
 * of the RGB
 */
typedef enum{RGB_RED,	/*!< Definition to select the color red */
			 RGB_GREEN,	/*!< Definition to select the color green */
			 RGB_BLUE,	/*!< Definition to select the color blue */
			 RGB_PURPLE, /*!< Definition to select the color purple */
			 RGB_YELLOW, /*!< Definition to select the color yellow */
			 RGB_CYAN,	/*!< Definition to select the color cyan */
			 RGB_WHITE	/*!< Definition to select the color white */
			} rgb_led_color_t;
/*
 	 \brief
 	 	 This function configures the GPIOs for the RGB LED and sets a safe value for PDOR.
 	 \param[in] void
 	 \return 1 if the configuration was done correctly.
*/
uint8_t RGB_initialize_all_colors(void);
/*
 	 \brief
 	 	 This function configures the GPIOs needed for only one color and assigns a safe value to PDOR.
 	 \param[in] color_name The color that is required to initialize.
 	 \return 1 if the color is valid, 0 if it is not.
*/
uint8_t RGB_initialize_one_color(rgb_led_color_t color_name);
/*
 	 \brief
 	 	 Clears the corresponding pin(s) to turn on the specified color
 	 \param[in] color_name The color that is required to turn on.
 	 \return 1 if the color is valid, 0 if it is not.
*/
uint8_t RGB_color_on(rgb_led_color_t color_name);
/*
 	 \brief
 	 	 Sets the corresponding pin(s) to turn off the specified color
 	 \param[in] color_name The color that is required to turn off.
 	 \return 1 if the color is valid, 0 if it is not.
*/
uint8_t RGB_color_off(rgb_led_color_t color_name);

#endif /* RGB_H_ */
