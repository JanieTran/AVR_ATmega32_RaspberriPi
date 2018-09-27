/*
 * Lab2_Task4_SPISlave.c
 *
 */ 

#ifndef F_CPU
#define F_CPU 12000000ul
#endif

#include <avr/io.h>
#include <util/delay.h>

void SPI_SlaveInit(void);
uint8_t SPI_SlaveReceive(void);
uint8_t result;
uint8_t tx;

int main(void)
{
	DDRA |= 1 << DDA0;
    SPI_SlaveInit();
	tx = 0;
	SPDR = 0x3f;
	
    while (1) {
		tx = SPI_SlaveReceive();
		if (tx == 0x8a) {
			PORTA |= 1 << PORTA0;
		}
    }
}

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