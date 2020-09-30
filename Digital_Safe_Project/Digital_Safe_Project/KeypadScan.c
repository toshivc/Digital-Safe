/*
 * KeypadScan.c
 *
 * Created: 9/28/2020 2:49:18 PM
 *  Author: Toshi & Ioanna
 */ 

// Include relevant file headers
#include <avr/io.h>
#include "KeypadScan.h"
#include "Delay.h"

//keypad hardware size
extern unsigned char keypad3x4;

// Define relevant variables
unsigned char key = 0xFF;
unsigned char portCValue = 0xFF;
unsigned char KeyPressed = 0x00;

//define lookup tables, in Initialise.c
extern const char col[4];
extern unsigned char AmountOfColumns;
extern unsigned char Keys[16];


// START FUNCTIONS

//**************************************************************************************************************************************************
// Function that checks if one key has been pressed 
unsigned char ReadOne() 
{
	// Set KeyPressed to 0
	KeyPressed = 0x00;
	
	while(1)	//can get rid of while loop, it just keeps reading until a key is pressed instead of only reading once when its called
	{

		// Scanning column: write the column mask to port C
		for (uint8_t j=0; j<AmountOfColumns; j++)
		{
			PORTC = col[j];			// Scan each column
			delay(1);				// Delay for 0.01 sec
			portCValue = PINC;			// Read port value from pinC
		
			// Begin stepping through each column to check if row has logic 0
			if (portCValue != col[j])
			{
				//rebounce??
				//Step through each key
				for(uint8_t k = 0; k < 16; k++)
				{
					if(portCValue == Keys[k])
					{
						key = k;
						//*portBPort = k;
						KeyPressed = 1;
						//break;						//return here instead of break??
						return key;
					}		
				}
			}
		}
	}
	return key;		//this should never execute
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//Check if key has been lifted. ie debounce?
void ReadNone (void)
{
	if(keypad3x4==1)
	{
		while((PINC&0x6A)!=0x6A);	//exits when PINC inputs are all high 
	}
	else
	{
		while((PINC&0x0F)!=0x0F);	//exits when PINC inputs are all high 
	}
	
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//Combine 6-8 digits into a passcode
uint32_t InputPasscode (void)
{
	uint32_t passcode = 0;
	for (int i =0; i<8; i++)
	{
		uint8_t keyValue = ReadOne();	//store digit pressed by user
		
		//check if key pressed is a digit
		
		if(keyValue==0xF)					//if # is pressed
		{
			return passcode;
		}
		
		PORTB = keyValue;
		ReadNone();						//waits until finger is lifted off button
		PORTB = 0x00;
		
		passcode = passcode*10 + keyValue;	//add each digit into a long int

	}
	return passcode;
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//is the input a digit