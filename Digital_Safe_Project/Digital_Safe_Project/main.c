/*
 * Digital_Safe_Project.c
 *
 * Created: 9/24/2020 11:57:08 AM
 * Author : Ioanna & Toshi
 */ 

// Include libraries
#include <avr/io.h>

// Include other project header files (.h)
#include "EEPROM.h"
#include "Delay.h"
#include "Display.h"
#include "Initialise.h"
#include "KeypadScan.h"
#include "Modes.h"

// Global variables
uint8_t debugCode = 0;

int main(void)
{
	// Initialise everything
    initTimers();
	initLEDs();
	initKeypad();
	
	/* DONT KNOW IF NECESSARY
	// Set all passcodes to zero 
	for (int i=0; i < 4; i++)
	{
		storePasscode(00000000, 0xA+i);		//stores the password 00000000 into user slot if no previous code has been set
	}
	*/


	// Start infinite loop
    while (1) 
    {
		for (int i = 0; i < 4; i++)	
		{
			uint8_t attempts = 0;		// Set number of attempts to 0
			if (ReadOne() == 0x0A+i)	// Check if user A B C or D is chosen
			{
				while (attempts < 3)	// Ensure number of passcode attempts < 3
				{
					uint32_t attemptPasscode = InputPasscode();		// Read the passcode from the keypad
					if (RecallPasscode(0x0A+i) == attemptPasscode)	// If the attempted passcode is equal to the stored passcode, UNLOCK
					{
						delay_ms(100);
						displayUnlock();
					}
					else		// If incorrect, display LOCK 
					{
						delay_ms(100);
						displayLock();
						attempts = attempts + 1;	// Increment number of attempts by 1
					}
				}
				// LOCKOUT when number of attempts is more than 3
				lockoutMode();
			}//
			
			
			else if (ReadOne() == 0x0E)		// If the * is pressed
			{
				delay_sec(5);				// Wait 5 seconds
				if (ReadOne() == 0x0E)		// If the * is still pressed (been held down for 5 seconds?)
				{
					// ENTER PROGRAMMING MODE - check for which user is pressed
					ProgramMode();
				}
			}
			
			else // If any other key is pressed
			{
				delay_ms(100);
				displayLock();
			}
		}		
    }
}
