/*
 * Signals.c
 *
 *  Created on: 12 mar. 2021
 *      Author: paula
 */


#include "Signals.h"
#include "GPIO.h"
#include "PIT.h"
#include "MK64F12.h"
#include "DAC.h"
#include "RGB.h"
#include "Bits.h"

#define SIZE_ARRAY 256


uint8_t g_c0_config={DACEN|DACRFS};
uint8_t g_buff_config={FALSE};


uint8_t g_square_counter = 0;
uint8_t g_triangle_counter = 0;
uint8_t g_sin_counter = 0;

uint8_t g_signal_case = 0;
typedef struct{
	wave_state_t signal;
	const struct gen_sen_state_t* next[POSIBLE_STATES];
}gen_sen_state_t;

const gen_sen_state_t GEN_SEN_SM[STATE_NUMBERS]=
{
		{TURN_OFF_STATE,{NO_SIGNAL, SQUARE_SIGNAL}},
		{SQUARE_WAVE_STATE,{SQUARE_SIGNAL, SIN_SIGNAL}},
		{SIN_WAVE_STATE,{SIN_SIGNAL, TRIANGLE_SIGNAL}},
		{TRIANGLE_WAVE_STATE,{TRIANGLE_SIGNAL, NO_SIGNAL}}
};

const uint16_t square_signal_wave[SIZE_ARRAY]=
{
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,0x0,0x0,0x0,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,
		0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF,0xFFF
};

const uint16_t triangle_signal_wave[SIZE_ARRAY]=
{
		0x0,0x20,0x40,0x60,0x80,0xA0,0xC0,0xE0,0x100,0x120,0x140,0x160,0x180,0x1A0,0x1C0,0x1E0,0x200,
		0x220,0x240,0x260,0x280,0x2A0,0x2C0,0x2E0,0x300,0x320,0x340,0x360,0x380,0x3A0,0x3C0,0x3E0,0x400,
		0x420,0x440,0x460,0x480,0x4A0,0x4C0,0x4E0,0x500,0x520,0x540,0x560,0x580,0x5A0,0x5C0,0x5E0,0x600,
		0x620,0x640,0x660,0x680,0x6A0,0x6C0,0x6E0,0x700,0x720,0x740,0x760,0x780,0x7A0,0x7C0,0x7E0,0x800,
		0x81F,0x83F,0x85F,0x87F,0x89F,0x8BF,0x8DF,0x8FF,0x91F,0x93F,0x95F,0x97F,0x99F,0x9BF,0x9DF,0x9FF,
		0xA1F,0xA3F,0xA5F,0xA7F,0xA9F,0xABF,0xADF,0xAFF,0xB1F,0xB3F,0xB5F,0xB7F,0xB9F,0xBBF,0xBDF,0xBFF,
		0xC1F,0xC3F,0xC5F,0xC7F,0xC9F,0xCBF,0xCDF,0xCFF,0xD1F,0xD3F,0xD5F,0xD7F,0xD9F,0xDBF,0xDDF,0xDFF,
		0xE1F,0xE3F,0xE5F,0xE7F,0xE9F,0xEBF,0xEDF,0xEFF,0xF1F,0xF3F,0xF5F,0xF7F,0xF9F,0xFBF,0xFDF,0xFFF,
		0xFDF,0xFBF,0xF9F,0xF7F,0xF5F,0xF3F,0xF1F,0xEFF,0xEDF,0xEBF,0xE9F,0xE7F,0xE5F,0xE3F,0xE1F,0xDFF,
		0xDDF,0xDBF,0xD9F,0xD7F,0xD5F,0xD3F,0xD1F,0xCFF,0xCDF,0xCBF,0xC9F,0xC7F,0xC5F,0xC3F,0xC1F,0xBFF,
		0xBDF,0xBBF,0xB9F,0xB7F,0xB5F,0xB3F,0xB1F,0xAFF,0xADF,0xABF,0xA9F,0xA7F,0xA5F,0xA3F,0xA1F,0x9FF,
		0x9DF,0x9BF,0x99F,0x97F,0x95F,0x93F,0x91F,0x8FF,0x8DF,0x8BF,0x89F,0x87F,0x85F,0x83F,0x81F,0x800,
		0x7E0,0x7C0,0x7A0,0x780,0x760,0x740,0x720,0x700,0x6E0,0x6C0,0x6A0,0x680,0x660,0x640,0x620,0x600,
		0x5E0,0x5C0,0x5A0,0x580,0x560,0x540,0x520,0x500,0x4E0,0x4C0,0x4A0,0x480,0x460,0x440,0x420,0x400,
		0x3E0,0x3C0,0x3A0,0x380,0x360,0x340,0x320,0x300,0x2E0,0x2C0,0x2A0,0x280,0x260,0x240,0x220,0x200,
		0x1E0,0x1C0,0x1A0,0x180,0x160,0x140,0x120,0x100,0xE0,0xC0,0xA0,0x80,0x60,0x40,0x20

};


const uint16_t sin_signal_wave[SIZE_ARRAY]=
{
		0x800,0x832,0x864,0x896,0x8C8,0x8FA,0x92C,0x95E,0x98F,0x9C0,0x9F1,0xA22,0xA52,0xA82,0xAB1,
		0xAE0,0xB0F,0xB3D,0xB6B,0xB98,0xBC5,0xBF1,0xC1C,0xC47,0xC71,0xC9A,0xCC3,0xCEB,0xD12,0xD39,
		0xD5F,0xD83,0xDA7,0xDCA,0xDED,0xE0E,0xE2E,0xE4E,0xE6C,0xE8A,0xEA6,0xEC1,0xEDC,0xEF5,0xF0D,
		0xF24,0xF3A,0xF4F,0xF63,0xF76,0xF87,0xF98,0xFA7,0xFB5,0xFC2,0xFCD,0xFD8,0xFE1,0xFE9,0xFF0,
		0xFF5,0xFF9,0xFFD,0xFFE,0xFFF,0xFFE,0xFFD,0xFF9,0xFF5,0xFF0,0xFE9,0xFE1,0xFD8,0xFCD,0xFC2,
		0xFB5,0xFA7,0xF98,0xF87,0xF76,0xF63,0xF4F,0xF3A,0xF24,0xF0D,0xEF5,0xEDC,0xEC1,0xEA6,0xE8A,
		0xE6C,0xE4E,0xE2E,0xE0E,0xDED,0xDCA,0xDA7,0xD83,0xD5F,0xD39,0xD12,0xCEB,0xCC3,0xC9A,0xC71,
		0xC47,0xC1C,0xBF1,0xBC5,0xB98,0xB6B,0xB3D,0xB0F,0xAE0,0xAB1,0xA82,0xA52,0xA22,0x9F1,0x9C0,
		0x98F,0x95E,0x92C,0x8FA,0x8C8,0x896,0x864,0x832,0x800,0x7CD,0x79B,0x769,0x737,0x705,0x6D3,
		0x6A1,0x670,0x63F,0x60E,0x5DD,0x5AD,0x57D,0x54E,0x51F,0x4F0,0x4C2,0x494,0x467,0x43A,0x40E,
		0x3E3,0x3B8,0x38E,0x365,0x33C,0x314,0x2ED,0x2C6,0x2A0,0x27C,0x258,0x235,0x212,0x1F1,0x1D1,
		0x1B1,0x193,0x175,0x159,0x13E,0x123,0x10A,0xF2,0xDB,0xC5,0xB0,0x9C,0x89,0x78,0x67,0x58,0x4A,
		0x3D,0x32,0x27,0x1E,0x16,0xF,0xA,0x6,0x2,0x1,0x0,0x1,0x2,0x6,0xA,0xF,0x16,0x1E,0x27,0x32,
		0x3D,0x4A,0x58,0x67,0x78,0x89,0x9C,0xB0,0xC5,0xDB,0xF2,0x10A,0x123,0x13E,0x159,0x175,0x193,
		0x1B1,0x1D1,0x1F1,0x212,0x235,0x258,0x27C,0x2A0,0x2C6,0x2ED,0x314,0x33C,0x365,0x38E,0x3B8,0x3E3,
		0x40E,0x43A,0x467,0x494,0x4C2,0x4F0,0x51F,0x54E,0x57D,0x5AD,0x5DD,0x60E,0x63F,0x670,0x6A1,0x6D3,
		0x705,0x737,0x769,0x79B,0x7CD

};

void turn_off_signal(void)
{
	GPIO_clear_pin(GPIO_C, bit_0);
	GPIO_clear_pin(GPIO_C, bit_9);
	DAC_config(DAC_0, g_c0_config, g_buff_config);
	DAC_out_buffer(0x0000);
}

void square_signal(void)
{
	RGB_color_off(RGB_WHITE);
	RGB_color_on(RGB_BLUE);
	GPIO_clear_pin(GPIO_C, bit_0);
	GPIO_clear_pin(GPIO_C, bit_9);
	GPIO_set_pin(GPIO_C, bit_0);
	DAC_out_buffer(square_signal_wave[g_square_counter]);
	g_square_counter++;
	if(g_square_counter>=SIZE_ARRAY)
	{
		g_square_counter = 0;
	}
}

void triangle_signal(void)
{
	RGB_color_off(RGB_WHITE);
	RGB_color_on(RGB_GREEN);
	GPIO_clear_pin(GPIO_C, bit_0);
	GPIO_clear_pin(GPIO_C, bit_9);
	DAC_out_buffer(triangle_signal_wave[g_triangle_counter]);
	g_triangle_counter++;
	if(g_triangle_counter>=SIZE_ARRAY)
	{
		g_triangle_counter = 0;
	}

}

void sin_signal(void)
{
	RGB_color_off(RGB_WHITE);
	RGB_color_on(RGB_RED);
	GPIO_clear_pin(GPIO_C, bit_0);
	GPIO_clear_pin(GPIO_C, bit_9);
	GPIO_set_pin(GPIO_C, bit_9);
	DAC_out_buffer(sin_signal_wave[g_sin_counter]);
	g_sin_counter++;
	if(g_sin_counter>=SIZE_ARRAY)
	{
		g_sin_counter = 0;
	}
}

void generator_signal(void)
{
	switch(g_signal_case)
	{
	case TURN_OFF_STATE:
		turn_off_signal();

	break;
	case SQUARE_WAVE_STATE:
		square_signal();
	break;
	case SIN_WAVE_STATE:
		sin_signal();
	break;
	case TRIANGLE_WAVE_STATE:
		triangle_signal();
	break;


	}
}






