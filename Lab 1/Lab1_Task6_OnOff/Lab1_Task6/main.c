/*
 * Lab1_Task6.c
 *
 * Created: 23-Jul-18 5:58:25 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int ledMode;

int main(void)
{
    // PB3 as output for LED
	DDRB |= 1 << DDB3;
	// PD3 as input from push button
	DDRD &= ~(1 << DDD3);
	
	// INTERRUPT INIT
	//============================================================
	// Set INT1 as external interrupt
	GICR |= 1 << INT1;
	// Interrupt request on rising edge of INT1
	MCUCR |= (1 << ISC11) | (1 << ISC10);
	// Enable global interrupt
	sei();
	
	ledMode = 1;
	
    while (1) 
    {
		// Toggle LED on and off
		if (ledMode) {
			PORTB |= 1 << PORTB3;
		} else {
			PORTB &= ~(1 << PORTB3);
		}
    }
}

ISR (INT1_vect) {
	_delay_ms(300);
	ledMode ^= 1;
}

int calculate_ocr(int duty_cycle) {
	return duty_cycle * 255 / 100;
}