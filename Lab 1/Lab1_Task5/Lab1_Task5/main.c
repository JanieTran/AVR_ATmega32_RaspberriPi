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
	// Clk source = clk/1024 => 12MHz/1024 = 11718Hz = 85us/cycle
	// Counting from 0-255 => 85us * 255 = 21675us = 21.675ms = 46Hz
	TCCR0 |= (1 << CS00) | (1 << CS02);
	
	// 1 second = 1000ms => 1000/21.675 = 46 counting cycles
	int counter = 0;
	int seconds = 0;
	
    while (1) 
    {
		while (!(TIFR & 1 << TOV0));
		TIFR |= 1 << TOV0;
		// Update counter after each counting cycles
		counter++;
		
		// After 61 counting cycles, increment seconds
		if (counter == 46) {
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

