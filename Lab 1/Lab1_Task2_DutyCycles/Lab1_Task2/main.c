/*
 * Lab1_Task2.c
 *
 * Created: 19-Jul-18 5:49:32 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 12000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>

#define PERIOD 10

int main(void)
{
	// PA0 as output
	DDRA |= 1 << DDA0;
    while (1) 
    {
		int cycle[7] = {10, 20, 30, 40, 50, 75, 100};
		
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 50; j++) {
				set_duty_cycle(cycle[i]);
			}
		}
		
    }
}

void set_duty_cycle(int duty) {
	int high = PERIOD * duty / 100;
	int low = PERIOD - high;
	
	PORTA |= 1 << PORTA0;
	_delay_ms(high);
	PORTA &= ~(1 << PORTA0);
	_delay_ms(low);
}