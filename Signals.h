/*
 * Signals.h
 *
 *  Created on: 12 mar. 2021
 *      Author: paula
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_




#include "stdint.h"
#include "MK64F12.h"

#define STATE_NUMBERS 4U
#define POSIBLE_STATES 2U
#define NO_SIGNAL &GEN_SEN_SM[0]
#define SQUARE_SIGNAL &GEN_SEN_SM[1]
#define SIN_SIGNAL &GEN_SEN_SM[2]
#define TRIANGLE_SIGNAL &GEN_SEN_SM[3]

typedef enum{
	TURN_OFF_STATE,
	SQUARE_WAVE_STATE,
	SIN_WAVE_STATE,
	TRIANGLE_WAVE_STATE
}wave_state_t;




void turn_off_signal(void);

void square_signal(void);

void triangle_signal(void);

void sin_signal(void);

void generator_signal(void);








#endif /* SIGNALS_H_ */
