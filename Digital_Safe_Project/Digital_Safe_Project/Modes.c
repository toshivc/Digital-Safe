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


// General Mode
void GeneralMode(void)
{

}


void ProgramMode(void)
{
	// ENTER PROGRAMMING MODE - check for which user is pressed
	for (int i = 0; i < 4; i++)
	{
		uint8_t attempts = 0;
		if (ReadOne() == 0x0A+i)	// Check if user A B C or D is chosen
		{
			while (attempts < 3)
			{
				uint32_t attemptPasscode = InputPasscode();		// Read the passcode from the keypad
				if (RecallPasscode(0x0A+i) == attemptPasscode)	// If the attempted passcode is equal to the stored passcode, UNLOCK
				{
					delay_ms(100);
					displayUnlock();
					// Set new passcode
					storePasscode(InputPasscode(), 0xA+i);		//stores the password 12345678 into user slot A
				}
				else
				{
					delay_ms(100);
					displayLock();
					attempts = attempts + 1;
				}
			}
			// LOCKOUT when number of attempts is more than 3
			lockoutMode();
		}
		else
		{
			delay_ms(100);
			displayLock();
		}
	}
}