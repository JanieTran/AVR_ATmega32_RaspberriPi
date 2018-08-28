/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#include <avr/io.h>
#include "TWI.h"

void TWI_Init(void) {
	// TWI Prescaler = 1
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));
	// TWI Bit Rate Register = 36
	// SCL freq = 8MHz / (16 + 2 * 32 * 1) = 100kHz;
	TWBR = 32;
	// Enable TWI
	TWCR |= 1 << TWEN;
}

void TWI_Start(void) {
	// Clear TWI Interrupt Flag
	// Make master, generate START condition
	// Activate TWI, take control over SCL and SDA
	TWCR |= (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);	
	
	// Wait until TWINT is successfully cleared
	while (!(TWCR & (1 << TWINT)));
}

void TWI_Stop(void) {
	// Clear TWI Interrupt Flag
	// Generate STOP condition
	// Activate TWI, take control over SCL and SDA
	TWCR |= (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);
	
	while (TWCR & (1 << TWSTO));
}

void TWI_Write(uint8_t data8) {
	// TWI Data Register
	TWDR = data8;
	// Clear TWI Interrupt Flag
	// Activate TWI, take control over SCL and SDA
	TWCR = (1 << TWEN) | (1 << TWINT);
	
	// Wait until TWINT is successfully cleared
	while (!(TWCR & (1 << TWINT)));
}

uint8_t TWI_AckRead(void) {
	// Clear TWI Interrupt Flag
	// Activate TWI, take control over SCL and SDA
	// TWI Enable Acknowledgement
	TWCR |= (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	
	// Wait until TWINT is successfully cleared
	while (!(TWCR & (1 << TWINT)));
	
	return TWDR;
}

uint8_t TWI_NoAckRead(void) {
	// Clear TWI Interrupt Flag
	// Activate TWI, take control over SCL and SDA
	TWCR = (1 << TWEN) | (1 << TWINT);
	
	// Wait until TWINT is successfully cleared
	while (!(TWCR & (1 << TWINT)));
	
	return TWDR;
}

uint8_t TWI_GetStatus(void) {
	uint8_t statusBits;
	// Read TWI Status Bit - TWSR[7:3]
	statusBits = TWSR & 0xF8;
	return statusBits;
}