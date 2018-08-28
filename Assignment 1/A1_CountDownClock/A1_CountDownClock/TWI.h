/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#ifndef TWI_H_
#define TWI_H_

void TWI_Init(void);
void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8_t data8);
uint8_t TWI_AckRead(void);
uint8_t TWI_NoAckRead(void);
uint8_t TWI_GetStatus(void);

#endif /* TWI_H_ */