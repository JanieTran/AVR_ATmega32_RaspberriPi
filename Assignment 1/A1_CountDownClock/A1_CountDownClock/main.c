/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#ifndef F_CPU
#define F_CPU 8000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>
#include "RTC.h"
#include "TWI.h"
#include "Dual7Segment.h"

//=====================================================
// Prototypes
//=====================================================

void GPIO_Config(void);

void ClearDisplay(void);

void INT1_Init(void);

void SevenSegDisplay(uint8_t value);
void WriteDigit1(uint8_t second);
void WriteDigit2(uint8_t second);

//=====================================================
// MAIN FUNCTION
//=====================================================

uint8_t second;
uint8_t rtcSecond;
uint8_t counting;
uint8_t finish;

int main(void)
{
	// Configuration
	GPIO_Config();
	ClearDisplay();
	TWI_Init();
	RTC_ResetSec();
	
	// Variables initialisation
	counting = 0;
	second = 0;
	rtcSecond = 0;
	finish = 0;
	
    while (1) {
		// Counting mode
		if (counting) {
			RTC_ReadSec(&rtcSecond);
			second = 59 - rtcSecond;	
			
			// Exit counting mode and toggle finish flag
			if (second == 0) {
				counting = 0;
				finish = 1;
			}
		}
		
		// Button is pushed, reset clock and
		// begin counting down
		if (PIND & 1 << PIND3) {
			_delay_ms(300);
			RTC_ResetSec();
			counting = 1;
		}
		
		// Display value of second
		WriteDigit1(second);
		WriteDigit2(second);
		
		// Toggle LED on when finish
		if (finish) {
			PORTC |= 1 << PORTC3;
			_delay_ms(2000);
			PORTC &= ~(1 << PORTC3);
			finish = 0;
		}
    }
}

//=====================================================
// GPIO Config
//=====================================================

void GPIO_Config(void) {
	// Port A (excluding PA6) as output for 7-segment digit 1
	DDRA = 0b10111111;
	// Port B (excluding PB7) as output for 7-segment digit 2
	DDRB = 0b01111111;
	// PD3 as input from push button
	DDRD &= ~(1 << DDD3);
	// PC3 as output to LED
	DDRC |= 1 << DDC3;
}

//=====================================================
// 7-Segment display
//=====================================================

void ClearDisplay(void) {
	PORTA = 0xFFul;
	PORTB = 0x7Ful;
}

void WriteDigit1(uint8_t second) {
	uint8_t tenth = second / 10;
	uint8_t digit;
	
	switch (tenth) {
		default: digit = 0xFF;	  break;
		case 0:  digit = B_ZERO;  break;
		case 1:  digit = B_ONE;   break;
		case 2:  digit = B_TWO;   break;
		case 3:  digit = B_THREE; break;
		case 4:  digit = B_FOUR;  break;
		case 5:  digit = B_FIVE;  break;
		case 6:  digit = B_SIX;   break;
		case 7:  digit = B_SEVEN; break;
		case 8:  digit = B_EIGHT; break;
		case 9:  digit = B_NINE;  break;
	}
	
	PORTB = digit;
}

void WriteDigit2(uint8_t second) {
	uint8_t unit = second % 10;
	uint8_t digit;
	
	switch (unit) {
		default: digit = 0xFF;	  break;
		case 0:  digit = A_ZERO;  break;
		case 1:  digit = A_ONE;  break;
		case 2:  digit = A_TWO;   break;
		case 3:  digit = A_THREE; break;
		case 4:  digit = A_FOUR;  break;
		case 5:  digit = A_FIVE;  break;
		case 6:  digit = A_SIX;   break;
		case 7:  digit = A_SEVEN; break;
		case 8:  digit = A_EIGHT; break;
		case 9:  digit = A_NINE;  break;
	}
	
	PORTA = digit;
}

