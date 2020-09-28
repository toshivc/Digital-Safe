/*
 * KeypadScan.c
 *
 * Created: 9/28/2020 2:49:18 PM
 *  Author: Toshi & Ioanna
 */ 

// Include relevant file headers
#include <avr/io.h>
#include "KeypadScan.h"


// Define relevant variables
unsigned char key = 0xFF;
unsigned char portCValue = 0xFF;
unsigned char KeyPressed = 0x00;
const char col[] = {0xEF, 0XDF, 0XBF, 0X7F};
unsigned char Keys[] = {0xD7, 0XEE, 0XDE, 0XBE, 0XED, 0XDD, 0XBD, 0XEB, 0XDB, 0XBB, 0XE7, 0XD7, 0XB7, 0X77, 0X7E, 0X7B}; // 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, *, #


// START FUNCTIONS

//**************************************************************************************************************************************************
// Function that checks if one key has been pressed 
unsigned char ReadOne() 
{
	// Set KeyPressed to 0
	KeyPressed = 0x00;
	
	// Scanning column: write the column mask to port C
	for (uint8_t j=0; j<3; j++)
	{
		PORTC = col[j];			// Scan each column
		for(uint8_t i=0; i<10; i++);		// Delay
		portCValue = PINC;			// Read port value from pinC
		
		// Begin stepping through each column to check if row has logic 0
		if (portCValue != col[j])
		{
			//rebounce??
			//Step through each key
			for(uint8_t k = 0; k < 12; k++)
			{
				if(portCValue == Keys[k])
				{
					key = k;
					//*portBPort = k;
					KeyPressed = 1;
					break;
				}		
			}
		}
	}
	return key;
}
//**************************************************************************************************************************************************
