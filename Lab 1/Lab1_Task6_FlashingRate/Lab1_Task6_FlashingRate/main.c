/*
 * Lab1_Task6_FlashingRate.c
 *
 * Created: 30-Jul-18 7:51:03 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int duty_cycles[] = {20, 50};
volatile int ledMode;

int main(void)
{
    // PB3 as output for LED
    DDRB |= 1 << DDB3;
    // PD3 as input from push button
    DDRD &= ~(1 << DDD3);
    
    initTimer();
    
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
	    // Toggle flashing rate of LED
	    OCR0 = calculate_ocr(duty_cycles[ledMode]);
    }
}

ISR (INT1_vect) {
	_delay_ms(200);
	ledMode ^= 1;
}

int calculate_ocr(int duty_cycle) {
	return duty_cycle * 255 / 100;
}

void initTimer() {
	// Fast PWM mode
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	// Clear OC0 on Compare Match, set OC0 at BOTTOM
	TCCR0 |= 1 << COM01;
	// Clk source = clk/1024 => 15625Hz = 64us/cycle
	// Counting from 0-255 => 64us * 255 = 16320us = 16.32ms
	TCCR0 |= (1 << CS00) | (1 << CS02);
}