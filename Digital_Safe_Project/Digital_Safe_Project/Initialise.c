/*
 * Initialise.c
 *
 * Created: 9/28/2020 2:40:32 PM
 *  Author: yoyos
 */ 

// File headers

#include "Initialise.h"
#include <avr/io.h>


// DEFINE VARIABLES
char errorFlag = 0;


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
	DDRC = 0xF0;		// Set rows to inputs and columns to outputs
	PORTC = 0x0F;		// Enable the pull-up resistors on the row inputs 
	PORTC = 0xFF;		// Set the columns to all on (idle state) & ensure pull-ups are still enabled
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