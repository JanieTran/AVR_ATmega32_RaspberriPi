/*
 * Lab1_Task2_100Hz.c
 *
 * Created: 30-Jul-18 8:05:08 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// PA0 as output
	DDRA |= 1 << DDA0;
	while (1)
	{
		PORTA |= 1 << PORTA0;
		_delay_ms(5);
		PORTA &= ~(1 << PORTA0);
		_delay_ms(5);
	}
}

