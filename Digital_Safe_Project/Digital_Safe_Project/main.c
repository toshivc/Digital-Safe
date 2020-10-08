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
	
	//// Set all passcodes to zero, useful when debugging
	//for (int i=0; i < 4; i++)
	//{
		//storePasscode(00000000, 0xA+i);		//stores the password 00000000 into user slot if no previous code has been set
	//}

	

	uint8_t noOfAttempts = 0;	// Set number of attempts to 0
	uint8_t previousUser = 0;	//store what the previous user was
	uint32_t attemptPasscode;	//stores the passcode input by the user

	// Start infinite loop
    while (1) 
    {
		uint8_t user = ReadOne();		//determines the first key pressed, may not always be a user
		
		if (previousUser != user)		//reset the attempts if a different user is pressed
		{
			noOfAttempts = 0;
		}
		
		
		if (isUser(user))	// Check if user A B C or D is chosen
		{
			displayUser(user);	//write the corresponding user LED pattern to the LEDs
			ReadNone();			//wait until a key is lifted
			PORTB = 0;
			
			previousUser = user;					//store the user, used to check if that user has had 3 attempts
			attemptPasscode = InputPasscode();		// Read the passcode from the keypad
				
			// UNLOCK // If the attempted passcode is equal to the stored passcode for the user specified
			if (RecallPasscode(user) == attemptPasscode)	
			{
				delay_ms(100);					//delay to make unlock sequence easier to see
				displayUnlock();
				
				while(ReadOne()!= 0x0F);		//wait until # is pressed to lock the safe
				ReadNone();
				PORTB = 0x00;
				noOfAttempts =0;				//reset the number of attempts on a succeful passcode
			}
			
			// LOCK // If passcode is incorrect
			else		
			{
				delay_ms(100);						//delay to make lock sequence easier to see
				displayLock();
				noOfAttempts = noOfAttempts + 1;	// Increment number of attempts by 1
					
				if (noOfAttempts >= 3)				// Ensure number of passcode attempts < 3
				{
					// LOCKOUT // when number of attempts is more than 3
					displayLockout();
				}
			}	
		}
			
			
		else if (user == 0x0E)		// If the * is pressed
		{
			PORTB = 0xFF;
			if(isHeld3s())			//check if the button is held for 3 seconds
			{
				displayProgramming();	//flash the LEDs to indicate entering programming mode
				PORTB = 0xFF;
				// ENTER PROGRAMMING MODE //
				ProgramMode();
			}	
			
			ReadNone();	//if * isnt held turn of the LEDs and exit
			PORTB = 0;
		}
			
		else // If any other key is pressed
		{
			delay_ms(100);
			displayIncorrect();
		}		
    }
}
