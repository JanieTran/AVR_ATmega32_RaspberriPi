/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#ifndef RTC_H_
#define RTC_H_

//=====================================================
// CONSTANTS DECLARATION
//=====================================================

#define RTC_WRITE_MODE 0xD0ul
#define RTC_READ_MODE 0xD1ul
#define RTC_SECOND_REG 0x00ul
#define RTC_CONTROL_REG 0x07ul

//=====================================================
// FUNCTIONS PROTOTYPES
//=====================================================

void RTC_ResetSec(void);
void RTC_ReadSec(uint8_t *rtcSecond);
uint8_t BCDtoDecimal(uint8_t value);

#endif /* RTC_H_ */