/**
	\file 	PIT.c
	\brief
		Source file for the PIT.h for Kinetis K64.
		It contains all the implementations for configuration and runtime functions.
	\author Paul Aguilar & Fernanda Galeana
	\date	25/02/2021
 */
#include "GPIO.h"
#include "Bits.h"
#include "MK64F12.h"
#include "PIT.h"


uint8_t interrupt_flag = 0x00;


void PIT_delay(PIT_timer_t pit_timer, My_float_pit_t system_clock , My_float_pit_t delay)
{

		My_float_pit_t timer_start_value = (uint32_t)((system_clock/2) * delay);
		//LOADS TIMER START VALUE
		PIT->CHANNEL[pit_timer].LDVAL = timer_start_value;
		//ENABLES PIT INTERRUPTION
		PIT_enable_interrupt(pit_timer);
		//TIMER ENABLE
		PIT->CHANNEL[pit_timer].TCTRL |= PIT_TCTRL_TEN_MASK;

}

void PIT_clock_gating(void)
{
	//ENABLES CLOCK GATE CONTROL FOR PIT
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

uint8_t PIT_get_interrupt_flag_status(void)
{
	//RETURNS THE VALUE OF THE FLAG CREATED
	//return(interrupt_flag);
	return PIT->CHANNEL[0].TFLG;
}


void PIT_clear_interrupt_flag(void)
{
	//flag value becomes 0
	interrupt_flag = 0x00;
}

void PIT_enable(void)
{
	//ENABLES PIT
	PIT->MCR &= ~(PIT_MCR_MDIS_MASK);
	PIT->MCR |= PIT_MCR_FRZ_MASK;
}

void PIT_enable_interrupt(PIT_timer_t pit)
{
	//PIT FLAG MASK IS CLEARED
	PIT->CHANNEL[pit].TFLG |= PIT_TFLG_TIF_MASK;

	//ENABLE THE INTERRUPT
	PIT->CHANNEL[pit].TCTRL |= PIT_TCTRL_TIE_MASK;
}

void PIT0_IRQHandler()
{
	volatile uint32_t dummyRead;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
	dummyRead = PIT->CHANNEL[0].TCTRL;
	interrupt_flag = 1;
}
