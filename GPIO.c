/**
	\file
	\brief
		This is the source file for the GPIO device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.
		i.e., this is the application programming interface (API) for the GPIO peripheral.
	\author J. Luis Pizano Escalante, luispizano@iteso.mx
	\date	18/02/2019
	\todo
	    Interrupts are not implemented in this API implementation.
 */
#include "MK64F12.h"
#include "GPIO.h"
#include "Bits.h"


uint8_t GPIO_clock_gating(gpio_port_name_t port_name)
{
	switch(port_name)/** Selecting the GPIO for clock enabling*/
			{
				case GPIO_A: /** GPIO A is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTA; /** Bit 9 of SIM_SCGC5 is  set*/
					break;
				case GPIO_B: /** GPIO B is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTB; /** Bit 10 of SIM_SCGC5 is set*/
					break;
				case GPIO_C: /** GPIO C is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTC; /** Bit 11 of SIM_SCGC5 is set*/
					break;
				case GPIO_D: /** GPIO D is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTD; /** Bit 12 of SIM_SCGC5 is set*/
					break;
				case GPIO_E: /** GPIO E is selected*/
					SIM->SCGC5 |= GPIO_CLOCK_GATING_PORTE; /** Bit 13 of SIM_SCGC5 is set*/
					break;
				default: /**If doesn't exist the option*/
					return(FALSE);
			}// end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

uint8_t GPIO_pin_control_register(gpio_port_name_t port_name, uint8_t pin,const gpio_pin_control_register_t*  pinControlRegister)
{

	switch(port_name)
			{
				case GPIO_A:/** GPIO A is selected*/
					PORTA->PCR[pin] = *pinControlRegister;
					break;
				case GPIO_B:/** GPIO B is selected*/
					PORTB->PCR[pin] = *pinControlRegister;
					break;
				case GPIO_C:/** GPIO C is selected*/
					PORTC->PCR[pin] = *pinControlRegister;
					break;
				case GPIO_D:/** GPIO D is selected*/
					PORTD->PCR[pin] = *pinControlRegister;
					break;
				case GPIO_E: /** GPIO E is selected*/
					PORTE->PCR[pin]= *pinControlRegister;
					break;
				default:/**If doesn't exist the option*/
					return(FALSE);
			}//end switch
	/**Successful configuration*/
	return(TRUE);
}// end function

void GPIO_write_port(gpio_port_name_t port_name, uint32_t data)
{
	switch(port_name)
			{
				case GPIO_A:/** GPIO A is selected*/
					GPIOA->PDOR = data;	/** Writes data in the port A**/
					break;
				case GPIO_B:/** GPIO B is selected*/
					GPIOB->PDOR = data; /** Writes data in the port B**/
					break;
				case GPIO_C:/** GPIO C is selected*/
					GPIOC->PDOR = data; /** Writes data in the port C**/
					break;
				case GPIO_D:/** GPIO D is selected*/
					GPIOD->PDOR = data; /** Writes data in the port D**/
					break;
				case GPIO_E: /** GPIO E is selected*/
					GPIOE->PDOR = data; /** Writes data in the port E**/
					break;
				default:/**If doesn't exist the option*/
					GPIOB->PDOR = data;
			}//end switch
}// end function

uint32_t GPIO_read_port(gpio_port_name_t port_name)
{
	uint32_t read_data;
	switch(port_name)
			{
				case GPIO_A: /** GPIO A is selected*/
					read_data = GPIOA->PDIR; /** Reads data from port A**/
					break;
				case GPIO_B: /** GPIO B is selected*/
					read_data = GPIOB->PDIR; /** Reads data from port B**/
					break;
				case GPIO_C: /** GPIO C is selected*/
					read_data = GPIOC->PDIR; /** Reads data from port C**/
					break;
				case GPIO_D: /** GPIO D is selected*/
					read_data = GPIOD->PDIR; /** Reads data from port D**/
					break;
				case GPIO_E: /** GPIO E is selected*/
					read_data = GPIOE->PDIR; /** Reads data from port E**/
					break;
				default:/**If doesn't exist the option*/
					read_data = FALSE;
			}//end switch
	/**Returns data read from specified port*/
	return(read_data);
}//end function
uint8_t GPIO_read_pin(gpio_port_name_t port_name, uint8_t pin)
{
	uint8_t read_pin_data;
	switch(port_name)
				{
					case GPIO_A: /** GPIO A is selected*/
						read_pin_data = (GPIOA->PDIR >> pin) && (0x0001); /** Reads data from the specified pin from port A **/
						break;
					case GPIO_B: /** GPIO B is selected*/
						read_pin_data = (GPIOB->PDIR >> pin) && (0x0001); /** Reads data from the specified pin from port B **/
						break;
					case GPIO_C: /** GPIO C is selected*/
						read_pin_data = (GPIOC->PDIR >> pin) && (0x0001); /** Reads data from the specified pin from port C **/
						break;
					case GPIO_D: /** GPIO D is selected*/
						read_pin_data = (GPIOD->PDIR >> pin) && (0x0001); /** Reads data from the specified pin from port D **/
						break;
					case GPIO_E: /** GPIO E is selected*/
						read_pin_data = (GPIOE->PDIR >> pin) && (0x0001); /** Reads data from the specified pin from port E **/
						break;
					default:	/**If doesn't exist the option*/
						read_pin_data = FALSE;
				}//end switch
	/**Returns data read from specified pin in the specified port*/
	return(read_pin_data);
}//end function
void GPIO_set_pin(gpio_port_name_t port_name, uint8_t pin)

{
	switch(port_name)
				{
					case GPIO_A:  /** GPIO A is selected*/
						GPIOA->PSOR |= ((0x1) << pin);	/** Sets specified pin to 1 in the port A**/
						break;
					case GPIO_B:  /** GPIO B is selected*/
						GPIOB->PSOR |= ((0x1) << pin); /** Sets specified pin to 1 in the port B**/
						break;
					case GPIO_C:  /** GPIO C is selected*/
						GPIOC->PSOR |= ((0x1) << pin); /** Sets specified pin to 1 in the port C**/
						break;
					case GPIO_D:  /** GPIO D is selected*/
						GPIOD->PSOR |= ((0x1) << pin); /** Sets specified pin to 1 in the port D**/
						break;
					case GPIO_E: /** GPIO E is selected*/
						GPIOE->PSOR |= ((0x1) << pin); /** Sets specified pin to 1 in the port E**/
						break;
					default:    /**If doesn't exist the option*/
						GPIOA->PSOR |= ((0x1) << pin);
				}//end switch
}//end function
void GPIO_clear_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
	{
	case GPIO_A:
		GPIOA->PCOR = (uint32_t)((0x01)<<(pin));
		break;
	case GPIO_B:
		GPIOB->PCOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_C:
		GPIOC->PCOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_D:
		GPIOD->PCOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_E:
		GPIOE->PCOR = (uint32_t)((0x01)<<(pin));

		break;

	}
}
void GPIO_toogle_pin(gpio_port_name_t port_name, uint8_t pin)
{
	switch(port_name)
	{
	case GPIO_A:
		GPIOA->PTOR = (uint32_t)((0x01)<<(pin));
		break;
	case GPIO_B:
		GPIOB->PTOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_C:
		GPIOC->PTOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_D:
		GPIOD->PTOR = (uint32_t)((0x01)<<(pin));

		break;
	case GPIO_E:
		GPIOE->PTOR = (uint32_t)((0x01)<<(pin));

		break;
	}
}
void GPIO_data_direction_port(gpio_port_name_t port_name ,uint32_t direction)
{
	switch(port_name)
	{
	case GPIO_A:
		GPIOA->PDDR |= direction;
		break;
	case GPIO_B:
		GPIOB->PTOR |= direction;

		break;
	case GPIO_C:
		GPIOC->PTOR |= direction;

		break;
	case GPIO_D:
		GPIOD->PTOR |= direction;

		break;
	case GPIO_E:
		GPIOE->PTOR |= direction;

		break;
	}
}
void GPIO_data_direction_pin(gpio_port_name_t port_name, uint8_t state, uint8_t pin)
{
	switch(port_name)
	{
	case GPIO_A:
		if (state == GPIO_OUTPUT)
		{
			GPIOA->PDDR |= (uint32_t)((0x01)<<(pin));
		}
		else
		{
			GPIOA->PDDR |= ~(uint32_t)((0x01)<<(pin));
		}
		break;
	case GPIO_B:
		if (state == GPIO_OUTPUT)
		{
			GPIOB->PDDR |= (uint32_t)((0x01)<<(pin));
		}
		else
		{
			GPIOB->PDDR |= ~(uint32_t)((0x01)<<(pin));
		}
		break;
	case GPIO_C:
		if (state == GPIO_OUTPUT)
		{
			GPIOC->PDDR |= (uint32_t)((0x01)<<(pin));
		}
		else
		{
			GPIOC->PDDR |= ~(uint32_t)((0x01)<<(pin));
		}
		break;
	case GPIO_D:
		if (state == GPIO_OUTPUT)
		{
			GPIOD->PDDR |= (uint32_t)((0x01)<<(pin));
		}
		else
		{
			GPIOD->PDDR |= ~(uint32_t)((0x01)<<(pin));
		}
		break;
	case GPIO_E:
		if (state == GPIO_OUTPUT)
		{
			GPIOE->PDDR |= (uint32_t)((0x01)<<(pin));
		}
		else
		{
			GPIOE->PDDR |= ~(uint32_t)((0x01)<<(pin));
		}
		break;
	}
}





