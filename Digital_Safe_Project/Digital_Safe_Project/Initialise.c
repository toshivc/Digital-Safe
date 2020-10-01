/*
 * Initialise.c
 *
 * Created: 9/28/2020 2:40:32 PM
 *  Author: Toshi & Ioanna
 */ 

// File headers

#include "Initialise.h"
#include <avr/io.h>


// DEFINE VARIABLES
char errorFlag = 0;


//3x4 Keypad Compile mode
unsigned char keypad3x4 = 1;		//set to 1 for 3x4

//Initialise lookup tables
unsigned char AmountOfColumns;

//3x4 UNCOMMENT TO USE AND COMMENT OUT 4x4 TABLE INITIALISATION
const uint8_t col[] = {0xFB, 0xFE, 0xEF, 0x00};
const uint8_t Keys[] = {0xF6, 0xF9, 0xFC, 0xED, 0xBB, 0xBE, 0xAF, 0xDB, 0xDE, 0xCF, 0x00, 0x00, 0x00, 0x00, 0xF3, 0xE7};	// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -, -, -, -, *, #
//4x4
//const uint8_t col[] = {0xEF, 0XDF, 0XBF, 0X7F};
//const uint8_t Keys[] = {0xD7, 0XEE, 0XDE, 0XBE, 0XED, 0XDD, 0XBD, 0XEB, 0XDB, 0XBB, 0X7E, 0X7D, 0X7B, 0X77, 0XE7, 0XB7}; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, *, #

// START FUNCTIONS

//****************************************************************************************
//	Initialise output LEDs - PORTB
void initLEDs(void)
{
	DDRB = 0xFF;		// Set all LEDs to outputs
	PORTB = 0x00;		// Turn all LEDs off
}
//****************************************************************************************


//****************************************************************************************
//	Initialise keypad - PORTC
void initKeypad(void)
{
	if(keypad3x4 == 1)
	{
		DDRC = 0x95;		// Set rows to inputs and columns to outputs
		PORTC = 0x6A;		// Enable the pull-up resistors on the row inputs
		PORTC = 0xFF;		// Set the columns to all on (idle state) & ensure pull-ups are still enabled
		
		AmountOfColumns =3;
	}
	else
	{
		DDRC = 0xF0;		// Set rows to inputs and columns to outputs
		PORTC = 0x0F;		// Enable the pull-up resistors on the row inputs
		PORTC = 0xFF;		// Set the columns to all on (idle state) & ensure pull-ups are still enabled
		
		AmountOfColumns =4;
	}

}
//****************************************************************************************


//****************************************************************************************
//Initialise Timers
void initTimers(void)
{
	//set timer counter to 0
	TCNT0 = 0x00;
	//set clock prescaler to divide by 1024
	TCCR0 |= (1<<CS00) | (0<<CS01) | (1<<CS02);
}
//****************************************************************************************