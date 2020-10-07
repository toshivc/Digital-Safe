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
	

	uint8_t attempts = 0;		// Set number of attempts to 0
	uint8_t previousUser = 0;	//store what the previous user was

	// Start infinite loop
    while (1) 
    {
		uint8_t user = ReadOne();		//CHANGED added instead of For loop, determines the first key pressed
		uint32_t attemptPasscode;
		
		if (previousUser != user)		//reset the attempts if a different user is pressed
		{
			attempts = 0;
		}
		
		
		if (isUser(user))	// Check if user A B C or D is chosen
		{
			displayUser(user);
			ReadNone();
			PORTB = 0;
			
			
			previousUser = user;					//store the user to check if that user has had 3 attempts
			attemptPasscode = InputPasscode();		// Read the passcode from the keypad
				
			if (RecallPasscode(user) == attemptPasscode)	// If the attempted passcode is equal to the stored passcode, UNLOCK
			{
				delay_ms(100);
				displayUnlock();
				while(ReadOne()!= 0x0F);		//wait until # is pressed to lock the safe
				ReadNone();
				PORTB = 0x00;
			}
			else		// If incorrect, display LOCK 
			{
				delay_ms(100);
				displayLock();
				attempts = attempts + 1;	// Increment number of attempts by 1
					
				if (attempts >= 3)	// Ensure number of passcode attempts < 3
				{
					// LOCKOUT when number of attempts is more than 3
					displayLockout();
				}
			}	
		}
			
			
		else if (user == 0x0E)		// If the * is pressed
		{
			PORTB = 0xFF;
			if(isHeld3s())
			{
				displayProgramming();
				PORTB = 0xFF;
				// ENTER PROGRAMMING MODE - check for which user is pressed
				ProgramMode();
			}	
			ReadNone();
			PORTB = 0;
		}
			
		else // If any other key is pressed
		{
			delay_ms(100);
			displayIncorrect();
		}		
    }
}
