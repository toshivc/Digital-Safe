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
#include "display.h"

// Global variables
uint8_t debugCode = 0;

int main(void)
{
	//initialise everything
    initTimers();
	initLEDs();
	
	displayUnlock();		//testing LEDs and delays, should flash various sequences on OUSB
	delay(100);
	displayLock();
	delay(100);
	displayProgramming();
	delay(5958);	//one min delay
	
    while (1) 
    {
		PORTB = 0xFF;
		delay(10);
		PORTB = 0x00;
		delay(30);
	
    }
}



