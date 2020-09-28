/*
 * KeypadScan.c
 *
 * Created: 9/28/2020 1:17:37 PM
 *  Author: Toshi & Ioanna
 */

 // Include file header
 #include "KeypadScan.h"
 #include <avr/io.h>
 #include "Initialise.h"
 
 // START FUNCTIONS
 
 //**************************************************************************************************************************************************
/* Function that checks if one key has been pressed 
unsigned char ReadOne() 
{
	// Set KeyPressed to 0
	keyPressed = 0x00;
	
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
					keyPressed = 1;
					break;
				}		
			}
		}
	}
	return key;
}
*/