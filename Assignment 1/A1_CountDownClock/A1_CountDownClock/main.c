/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#include <avr/io.h>

//=====================================================
// CONSTANTS DECLARATION
//=====================================================

#define RTC_WRITE_MODE 0xD0ul
#define RTC_READ_MODE 0xD1ul
#define RTC_SECOND_REG 0x00ul

//=====================================================
// FUNCTIONS DECLARATION
//=====================================================

// TWI functions
void InitialiseTWI(void);
void StartTWI(void);
void StopTWI(void);
void WriteTWI(uint8_t data8);
uint8_t AckReadTWI(void);
uint8_t NoAckReadTWI(void);
uint8_t TWIGetStatus(void);

// RTC functions
void RTC_ResetSec(void);
uint8_t RTC_ReadSec(void);

//=====================================================
// MAIN FUNCTION
//=====================================================

uint8_t second;

int main(void)
{
    
    while (1) {
		
    }
}

//=====================================================
// FUNCTIONS BODY
//=====================================================

// TWI functions

void InitialiseTWI(void) {
	// TWI Prescaler = 1
	TWSR |= ~((1 << TWPS1) | (1 << TWPS0));
	// TWI Bit Rate Register = 12
	// SCL freq = 12MHz / (16 + 2 * 12 * 1) = 300kHz;
	TWBR = 12;
}

void StartTWI(void) {
	// Clear TWI Interrupt Flag
	TWCR |= 1 << TWINT;
	// Make master, generate START condition
	TWCR |= 1 << TWSTA;
	// Activate TWI, take control over SCL and SDA
	TWCR |= 1 << TWEN;
	// Wait until TWINT is successfully cleared
	while (TWCR & 1 << TWINT);
}

void StopTWI(void) {
	// Clear TWI Interrupt Flag
	TWCR |= 1 << TWINT;
	// Generate STOP condition
	TWCR |= 1 << TWSTO;
	// Activate TWI, take control over SCL and SDA
	TWCR |= 1 << TWEN;
}

void WriteTWI(uint8_t data8) {
	// TWI Data Register
	TWDR = data8;
	// Clear TWI Interrupt Flag
	TWCR |= 1 << TWINT;
	// Activate TWI, take control over SCL and SDA
	TWCR |= 1 << TWEN;
	// Wait until TWINT is successfully cleared
	while (TWCR & 1 << TWINT);
}

uint8_t AckReadTWI(void) {
	// Clear TWI Interrupt Flag
	TWCR |= 1 << TWINT;
	// Activate TWI, take control over SCL and SDA
	TWCR |= 1 << TWEN;
	// TWI Enable Acknowledgement
	TWCR |= 1 << TWEA;
	// Wait until TWINT is successfully cleared
	while (TWCR & 1 << TWINT);
	return TWDR;
}

uint8_t NoAckReadTWI(void) {
	// Clear TWI Interrupt Flag
	TWCR |= 1 << TWINT;
	// Activate TWI, take control over SCL and SDA
	TWCR |= 1 << TWEN;
	// Wait until TWINT is successfully cleared
	while (TWCR & 1 << TWINT);
	return TWDR;
}

uint8_t TWIGetStatus(void) {
	uint8_t statusBits;
	// Read TWI Status Bit - TWSR[7:3]
	statusBits = TWSR & 0xF8;
	return statusBits;
}

// RTC functions

uint8_t RTC_ReadSec(void) {
	StartTWI();
	
	// Send Write request
	WriteTWI(RTC_WRITE_MODE);
	// Request address for Second
	WriteTWI(RTC_SECOND_REG);
	
	StopTWI();
	
	// Begin reading
	
	StartTWI();
	
	// Send Read request
	WriteTWI(RTC_READ_MODE);
	// Read from Second address with ACK
	second = AckReadTWI();
	
	StopTWI();
}

void RTC_ResetSec(void) {
	StartTWI();
	
	// Send Write request
	WriteTWI(RTC_WRITE_MODE);
	// Request address for Second
	WriteTWI(RTC_SECOND_REG);
	
	// Reset Second value to 0
	WriteTWI(0);
	
	StopTWI();
}
