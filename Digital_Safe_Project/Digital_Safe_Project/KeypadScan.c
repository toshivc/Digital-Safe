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
#include "Display.h"

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
			delay_ms(10);				// Delay for 0.01 sec
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
		
		if(keyValue==0xF)					//if # is pressed
		{
			return passcode;
		}
		
		//check if key pressed is a digit
		if(isDigit(keyValue))
		{
			PORTB = displayKeys(keyValue);	// output key being pressed to LEDs
			ReadNone();						//waits until finger is lifted off button
			PORTB = 0x00;
			
			passcode = passcode*10 + keyValue;	//add each digit into a long int
		}
		else
		{
			//not a valid input
			i--;		//dont increment length counter if not valid
			displayIncorrect();
			
		}	
	}
	/*
	while(!(ReadOne()==0xF));		//wait until reads a *
	return passcode	; */
	
	if((ReadOne()==0xF))		//if next key is a #
	{
		return passcode	;
	}
	else
	{
		return 0;
	}	
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//is the input a letter, a,b,c, or d. returns 1 if a valid user code
uint8_t isUser (uint8_t buttonPressed)
{
	switch(buttonPressed)
	{
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		return 1;
		
		default:	//invalid user code		Set some debug flag here
		return 0;
	}
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//is the user input a digit. returns 1 if value is a digit
uint8_t isDigit (uint8_t buttonPressed)
{
	switch(buttonPressed)
	{
		case 0x00:
		case 0x01:
		case 0x02:
		case 0x03:
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x07:
		case 0x08:
		case 0x09:
		return 1;
		
		default:	//invalid user code		Set some debug flag here
		return 0;
	}
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
//Return one if the selected key has been held for 3 seconds. return 0 if not
uint8_t isHeld3s (void)
{
	for(uint8_t i = 0; i<255; i++)
	{
		delay_ms(12);			//0.012*255 =3.06secs
		if((PINC&0x0F)==0x0F)
		{
			return 0;
		}
	}
	return 1;
}
//**************************************************************************************************************************************************

//**************************************************************************************************************************************************
uint8_t DigitCount(uint32_t NewPasscode)
{
	uint8_t count = 0;
	while (NewPasscode != 0)
	{
		NewPasscode /= 10;
		++count;
	}
	return count;
}
