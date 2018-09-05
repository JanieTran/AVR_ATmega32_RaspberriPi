/*
 * Lab2_Task1.c
 *
 * Created: 05-Sep-18 6:53:35 PM
 * Author : Dell
 */ 
#ifdef F_CPU
#define F_CPU 12000000ul
#endif

#include <avr/io.h>

//================================================================
// CONSTANTS
//================================================================

#define ADC5_POT 0x05
#define ADC6_LDR 0x06

//================================================================
// FUNCTION PROTOTYPES
//================================================================

// Timer0
void Timer0_Init(void);

// ADC
void ADC_Init(void);
uint8_t ADC_Read(uint8_t channel);

//================================================================
// MAIN FUNCTION
//================================================================

uint8_t valueADC;

int main(void)
{
	// PB3 as output for LED
	DDRB |= 1 << DDB3;
	
	// Register configuration
	Timer0_Init();
	ADC_Init();
	
    while (1) 
    {
		OCR0 = ADC_Read(ADC5_POT);
    }
}

//================================================================
// FUNCTION BODY
//================================================================

// Timer0
//---------------------------------

void Timer0_Init() {
	// Set Fast PWM mode
	TCCR0 |= (1 << WGM00) | (1 << WGM01);
	// Clear OC0 on Compare Match, set OC0 at BOTTOM
	TCCR0 |= 1 << COM01;
	// Clk source = clk/1024 => 12MHz/1024 = 11718Hz = 85us/cycle
	// Counting from 0-255 => 85us * 255 = 21675us = 21.675ms = 46Hz
	TCCR0 |= (1 << CS00) | (1 << CS02);
}

// ADC
//---------------------------------

void ADC_Init() {
	// AREF, Internal Vref turned off
	ADMUX &= ~(0b11 << REFS0);
	// Left Adjust Result
	ADMUX |= 1 << ADLAR;
	
	// ADC Enable
	ADCSRA |= 1 << ADEN;
	// ADC Prescaler = 128
	ADCSRA |= 0b111 << ADPS0;
}

uint8_t ADC_Read(uint8_t channel) {
	// Select ADC channel
	ADMUX |= channel << MUX0;
	
	// Start single conversion
	ADCSRA |= 1 << ADSC;
	// Wait until conversion complete
	while (!(ADCSRA & 1 << ADIF));
	
	// Clear ADIF
	ADCSRA |= 1 <<  ADIF;
	
	return ADCH;
}