/*
 * Lab1_Task1.c
 *
 * Created: 17-Jul-18 5:30:19 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 12000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// PA0 and PA1 as output
	DDRA |= 0x03 << 0;
    while (1) 
    {
		PORTA |= 0x03 << 0;
		_delay_ms(200);
		PORTA &= ~(0x03 << 0);
		_delay_ms(200);
    }
}

