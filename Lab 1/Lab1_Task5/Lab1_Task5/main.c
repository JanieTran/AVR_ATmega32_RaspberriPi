/*
 * Lab1_Task5.c
 *
 * Created: 23-Jul-18 5:30:33 PM
 * Author : Dell
 */ 

#include <avr/io.h>


int main(void)
{
    // PA0 as output for LED
	DDRA |= 1 << DDA0;
	
	// TIMER0 INIT
	// Mode: normal <= 0x00 << WGM00, WGM01 (default)
	// Clk source = clk/1024 => 15625Hz = 64us/cycle
	// Counting from 0-255 => 64us * 255 = 16320us = 16.32ms
	TCCR0 |= (1 << CS00) | (1 << CS02);
	
	// 1 second = 1000ms => 1000/16.32 = 61.27 counting cycles
	int counter = 0;
	int seconds = 0;
	
    while (1) 
    {
		while (!(TIFR & 1 << TOV0));
		TIFR |= 1 << TOV0;
		// Update counter after each counting cycles
		counter++;
		
		// After 61 counting cycles, increment seconds
		if (counter == 61) {
			counter = 0;
			seconds++;
		}
		
		// Toggle LED after 5 second
		if (seconds == 5) {
			seconds = 0;
			PORTA ^= 1 << PORTA0;
		}
    }
}

