
#include "MK64F12.h"
#include "GPIO.h"
#include "Delay.h"
#include "Bits.h"
#include "RGB.h"
#include "Switches.h"
#include "PIT.h"
#include "NVIC.h"


/**Delay constant that allows to wait a brief moment so the switch can be read correctly*/
#define DELAY_CONST 650000
/**Global variables to register the number of times a switch has been pressed*/
int g_counter_sw2 = 0;		//For switch 2
int g_counter_sw3 = 0;		//For switch 3
/**Functions that change the color of the LED when a switch is pressed*/
void change_color_sw2(int counter);		//For switch 2
void change_color_sw3(int counter);		//For switch 3
void change_color_white(int counter);		//For switch 3

void (*ptr_funcion[2])(int)={change_color_sw2, change_color_white};

#define SYSTEM_CLOCK_LED (21000000U)
#define DELAY_LED (100000)

uint16_t counter_for_case = 0;

int main(void) {
	int value = 0;

	PIT_clock_gating();
	PIT_enable();
	PIT_enable_interrupt(PIT_0);

	RGB_initialize_all_colors(); /**RGB configuration and initialization*/
	SW2_config();				 /**SW2 configuration and initialization*/
	SW3_config();				 /**SW3 configuration and initialization*/
	RGB_color_off(RGB_WHITE);	 /**Color for initial state*/

	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_6);
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ, PRIORITY_8);

	GPIO_callback_init(GPIO_A,case_value(value));

	NVIC_global_enable_interrupts;
		while(1)
		{
				if(FALSE == sw_state(SW2))
				{
					RGB_color_on(RGB_WHITE);
					PIT_delay(PIT_0,SYSTEM_CLOCK_LED, DELAY_LED);
					RGB_color_off(RGB_WHITE);
					PIT_delay(PIT_0,SYSTEM_CLOCK_LED, DELAY_LED);
					RGB_color_on(RGB_WHITE);
					PIT_delay(PIT_0,SYSTEM_CLOCK_LED, DELAY_LED);
					RGB_color_off(RGB_WHITE);
					while(1)
					{
						if(FALSE == sw_state(SW2))
						{
							RGB_color_on(RGB_WHITE);
							PIT_delay(PIT_0,SYSTEM_CLOCK_LED, DELAY_LED);
							RGB_color_off(RGB_WHITE);


							switch(value)
							{
							case(1):
								RGB_color_off(RGB_BLUE);

							break;
							case(2):
								RGB_color_off(RGB_GREEN);
							break;
							case(3):
								RGB_color_off(RGB_RED);
							break;
							case(4):
								RGB_color_off(RGB_YELLOW);
							break;
							case(5):
								RGB_color_off(RGB_PURPLE);
							break;
							case(6):
								RGB_color_off(RGB_CYAN);
							break;
							}

						}
					}
				}
		}


    return 0 ;
}

void case_value (value)
{
	if(FALSE == sw_state(SW3))
	{
		value +=1;
	}
		return value;
}

