/*
 * Delay.c
 *
 * Created: 27/09/2020 10:24:38 PM
 *  Author: Ioanna & Toshi
 */ 
#include <avr/io.h>

// Start functions
//****************************************************************************************
//Initialise Timers
void initTimers(void)
{
	//set timer counter to 0
	TCNT0 = 0x00;
	//set clock prescaler to divide by 1024
	TCCR0 |= (1<<CS00) | (0<<CS01) | (1<<CS02);
}
//****************************************************************************************

//****************************************************************************************
//Timer with minimum time of 0.01 seconds, max time of 11mins
void delay(uint16_t delayTime)
{
	//12MHz divided by 1024 is 11.718KHz, or clock time of 85.3micro seconds
	//multiplied by 118 gives 0.010069 seconds
	
	TCNT0 = 0x00;		//reset timer to 0
	OCR0 = 118;			//set compare register 
	TIFR = (1<<OCF0);	//reset compare flag
	
	uint16_t overflowCounter = 0;
	
	while (1)
	{
		while((TIFR & (1<<OCF0))==0); //while OCF0, overflow flag is 0
		TCNT0 = 0x00;		//reset timer to 0
		TIFR = (1<<OCF0); //reset compare flag
		overflowCounter++;
		if (overflowCounter >= delayTime)
		{
			return;
		}
	}	
}
//****************************************************************************************