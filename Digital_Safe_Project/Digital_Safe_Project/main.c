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

// Global variables
uint8_t debugCode = 0;

int main(void)
{
	// Initialise everything
    initTimers();
	initLEDs();
	initKeypad();
	
	storePasscode(12345678, 0xA);		//stores the password 12345678 into user slot A
	
    while (1) 
    {
		uint32_t attemptPasscode = InputPasscode();		//read the passcode from the keypad
		
		if(RecallPasscode(0xA)==attemptPasscode)		//check if correct
		{
			delay(10);
			displayUnlock();
		}
		else
		{
			delay(10);
			displayLock();
		}
		
    }
}
