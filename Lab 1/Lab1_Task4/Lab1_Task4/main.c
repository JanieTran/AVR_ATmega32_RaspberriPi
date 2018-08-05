/*
 * Lab1_Task4.c
 *
 * Created: 23-Jul-18 4:45:32 PM
 * Author : Dell
 */ 

#include <avr/io.h>


int main(void)
{
    // PB3 as output for LED
	DDRB |= 1 << DDB3;
	
	// TIMER0 INIT
	// Set Fast PWM mode
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	// Clear OC0 on Compare Match, set OC0 at BOTTOM
	TCCR0 |= 1 << COM01;
	// Clk source = clk/1024 => 12MHz/1024 = 11718Hz = 85us/cycle
	// Counting from 0-255 => 85us * 255 = 21675us = 21.675ms = 46Hz
	TCCR0 |= (1 << CS00) | (1 << CS02);
	
	// Output compare values required
	int duty_cycles[] = {10, 20, 30, 40, 50, 75, 100};
	
    while (1) 
    {
		//for (int i = 0; i < 7; i++) {
			//for (int j = 0; j < 200; j++) {
				OCR0 = calculate_ocr(duty_cycles[2]);
			//}
		//}
    }
}

int calculate_ocr(int duty_cycle) {
	return duty_cycle * 255 / 100;
}