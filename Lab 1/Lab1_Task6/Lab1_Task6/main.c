/*
 * Lab1_Task6.c
 *
 * Created: 23-Jul-18 5:58:25 PM
 * Author : Dell
 */ 

#include <avr/io.h>


int main(void)
{
    // PB3 as output for LED
	DDRB |= 1 << DDB3;
	
	// TIMER0 INIT
	
	
	// INTERRUPT INIT
	// Interrupt request on rising edge of INT1
	MCUCR |= (1 << ISC10) | (1 << ISC11);
	
    while (1) 
    {
		
    }
}

