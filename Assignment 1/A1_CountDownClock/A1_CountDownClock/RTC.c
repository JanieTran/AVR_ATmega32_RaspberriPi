/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#include <avr/io.h>
#include "RTC.h"
#include "TWI.h"

void RTC_ReadSec(uint8_t *rtcSecond) {
	TWI_Start();
	
	// Send Write request
	TWI_Write(RTC_WRITE_MODE);
	// Request address for Second
	TWI_Write(RTC_SECOND_REG);
	
	//TWI_Stop();
	
	// Begin reading
	
	TWI_Start();
	
	// Send Read request
	TWI_Write(RTC_READ_MODE);
	// Read from Second address without ACK
	uint8_t value = TWI_NoAckRead();
	*rtcSecond = BCDtoDecimal(value);
	
	TWI_Stop();
}

void RTC_ResetSec(void) {
	TWI_Start();
	
	// Send Write request
	TWI_Write(RTC_WRITE_MODE);
	// Request address for Second
	TWI_Write(RTC_SECOND_REG);
	
	// Reset Second value to 0
	TWI_Write(0x00ul);
	
	TWI_Stop();
}

uint8_t BCDtoDecimal(uint8_t value) {
	uint8_t tenth = value >> 4;
	uint8_t unit = value & 0x0Ful;
	
	return tenth * 10 + unit;
}