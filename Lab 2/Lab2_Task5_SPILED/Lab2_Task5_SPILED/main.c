/*
 * Lab2_Task5_SPILED.c
 *
 * Created: 27/09/2018 11:54:43 AM
 * Author : Dell
 */ 

#ifndef F_CPU
#define F_CPU 12000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>

//================================================================
// CONSTANTS
//================================================================

#define ADC5_POT 0x05
#define ADC6_LDR 0x06

//================================================================
// VARIABLES AND FUNCTIONS PROTOTYPES
//================================================================

// ADC
//---------------------------------

uint8_t mode;

void ADC_Init(void);
uint8_t ADC_Read(uint8_t channel);

// SPI
//---------------------------------

uint8_t SPI_SlaveReceive(void);
uint8_t result;
uint8_t tx;

void SPI_SlaveInit(void);

//================================================================
// MAIN FUNCTION
//================================================================

int main(void)
{
	// PA0 output to LED
    DDRA |= 0b111 << DDA0;
	
	// Initialisation
	ADC_Init();
	SPI_SlaveInit();
	
	mode = 0;
	SPDR = 0x00;
	tx = 0;
	
    while (1) {						
		tx = SPI_SlaveReceive();
		
		if (tx == 0x19) {
			PORTA ^= 1 << PORTA0;
			mode = !mode;
		}
		
		if (mode) {
			SPDR = ADC_Read(ADC5_POT);
		}
    }
}

//================================================================
// FUNCTION BODY
//================================================================

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

// SPI
//---------------------------------

void SPI_SlaveInit() {
	// Set PB6 - MISO output
	DDRB = 1 << DDB6;
	// SPI Clk prescaler
	SPCR = 0b11 << SPR0;
	// Enable SPI Mode 0
	SPCR |= 1 << SPE;
}

uint8_t SPI_SlaveReceive() {
	// Wait for reception complete
	while (!(SPSR & 1 << SPIF));
	// Return Data Register
	return SPDR;
}