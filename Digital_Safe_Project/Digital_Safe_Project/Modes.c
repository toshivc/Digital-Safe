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

//**************************************************************************************************************************************************
//Same functionality as the general mode but with the LEDs indicating the user is in PROGRAMMING mode and passcodes can be stored into EEPROM
void ProgramMode(void)
{
	ReadNone();						//wait until nothing is pressed, otherwise user could still be holding *
	uint8_t noOfAttempts = 0;		// Set number of attempts to 0
	
	while(1)
	{
	
		uint8_t user = ReadOne();		//determines the first key pressed, may not always be a user
		uint32_t attemptPasscode;
	
	
		if (isUser(user))	// Check if user A B C or D is chosen
		{
			displayUser(user);	//write the corresponding user LED pattern to the LEDs
			ReadNone();
			PORTB = 0xFF;
		
			attemptPasscode = InputPasscode();		// Read the passcode from the keypad
			
			
			if (RecallPasscode(user) == attemptPasscode)	// If the attempted passcode is equal to the stored passcode, UNLOCK
			{
				delay_ms(100);
				displayUnlockProg();
				ReadNone();
				PORTB =0xff;
					
				/////////////////////////////////////////////////////////
				uint32_t NewPassword = InputPasscode();
				uint8_t NewPasswordSize = DigitCount(NewPassword);
					
				if((NewPasswordSize >= 6)&& (NewPasswordSize <= 8))
				{
					storePasscode(NewPassword,user);
					displayUnlock();
					while(ReadOne()!= 0x0F);		//wait until # is pressed to lock the safe
					ReadNone();
					PORTB = 0x00;
					noOfAttempts = 0;
					return;
				}
			}
			
			else		// If incorrect, display LOCK
			{
				delay_ms(100);
				displayLock();
				ReadNone();
				PORTB =0xff;
				
				noOfAttempts = noOfAttempts + 1;	// Increment number of attempts by 1
					
				if (noOfAttempts >= 3)	// Ensure number of passcode attempts < 3
				{
					// LOCKOUT when number of attempts is more than 3
					displayLockout();
					return;
				}
			}
		}
		
		
		else // If any other key is pressed
		{
			delay_ms(100);
			displayIncorrect();
			PORTB = 0xFF;
		}
	}
}