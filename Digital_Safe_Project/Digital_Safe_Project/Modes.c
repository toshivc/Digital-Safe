/*
 * Modes.c
 *
 * Created: 10/4/2020 9:14:42 PM
 *  Author: Toshi & Ioanna */

// Include relevant file headers
#include <avr/io.h>
#include "KeypadScan.h"
#include "Modes.h"
#include "Display.h"
#include "Delay.h"
#include "EEPROM.h"


// General Mode
void GeneralMode(void)
{

}


void ProgramMode(void)
{
	ReadNone(); //wait until nothing is pressed
	uint8_t attempts = 0;		// Set number of attempts to 0
	// ENTER PROGRAMMING MODE - check for which user is pressed
	while(1)
	{
		
		uint8_t user = ReadOne();		//CHANGED added instead of For loop, determines the first key pressed
		uint32_t attemptPasscode;
	
	
		if (isUser(user))	// Check if user A B C or D is chosen
		{
			displayUser(user);
			ReadNone();
			PORTB = 0;
		
			if (attempts < 3)	// Ensure number of passcode attempts < 3		//CHANGED from while to If as it would always stay in the while loop
			{
				attemptPasscode = InputPasscode();		// Read the passcode from the keypad
			
				if (RecallPasscode(user) == attemptPasscode)	// If the attempted passcode is equal to the stored passcode, UNLOCK
				{
					delay_ms(100);
					displayUnlockProg();
					
					/////////////////////////////////////////////////////////
					uint32_t NewPassword = InputPasscode();
					uint8_t NewPasswordSize = DigitCount(NewPassword);
					
					if((NewPasswordSize >= 6)&& (NewPasswordSize <= 8))
					{
						storePasscode(NewPassword,user);
						displayUnlockProg();
						attempts = 0;
						return;
					}

				}
				else		// If incorrect, display LOCK
				{
					delay_ms(100);
					displayLock();
					attempts = attempts + 1;	// Increment number of attempts by 1
				}
			}
			else
			{
				// LOCKOUT when number of attempts is more than 3
				
				displayLockout();
				return;
			}
		}
		else // If any other key is pressed
		{
			delay_ms(100);
			displayIncorrect();
		}
	}
}