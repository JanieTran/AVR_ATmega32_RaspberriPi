/*
 * GPIO_Tutorial.c
 *
 * Created: 10-Jul-18 5:19:46 PM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 16000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB |= 0xFF;
	
    while (1) 
    {
		//int i;
		//for(i = 0; i < 8; i++) {
			//PORTB |= 1 << i;
			//_delay_ms(500);
			//PORTB &= ~0xFF;
		//}
		
		PORTB |= 1 << PORTB0;
		_delay_us(10);
		PORTB &= ~(1 << PORTB0);
		_delay_us(90);
    }
}
