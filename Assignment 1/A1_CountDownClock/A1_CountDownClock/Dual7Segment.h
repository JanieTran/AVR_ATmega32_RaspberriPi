/* RMIT University Vietnam
 * EEET2490 - Embedded System: Operating Systems & Interfacing
 * Assignment 2
 *
 * Student Name : Tran Thi Hong Phuong
 * Student ID: s3623386
 * Date: 20th August, 2018
 */ 

#ifndef DUAL7SEGMENT_H_
#define DUAL7SEGMENT_H_

//=====================================================
// CONSTANTS DECLARATION
//=====================================================

#define A_ZERO	~(0b00111111)
#define A_ONE	~(0b00000110)
#define A_TWO	~(0b10011011)
#define A_THREE	~(0b10001111)
#define A_FOUR	~(0b10100110)
#define A_FIVE	~(0b10101101)
#define A_SIX	~(0b10111101)
#define A_SEVEN	~(0b00000111)
#define A_EIGHT ~(0b10111111)
#define A_NINE	~(0b10101111)

#define B_ZERO  ~(0b00111111)
#define B_ONE	~(0b00000110)
#define B_TWO	~(0b01011011)
#define B_THREE ~(0b01001111)
#define B_FOUR	~(0b01100110)
#define B_FIVE	~(0b01101101)
#define B_SIX	~(0b01111101)
#define B_SEVEN ~(0b00000111)
#define B_EIGHT ~(0b01111111)
#define B_NINE	~(0b01101111)

#endif /* DUAL7SEGMENT_H_ */