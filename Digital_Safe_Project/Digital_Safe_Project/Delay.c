/*
 * Delay.c
 *
 * Created: 27/09/2020 10:24:38 PM
 *  Author: Ioanna & Toshi
 */ 
#include <avr/io.h>

// Start functions


//***************************************************************************************
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
// *****************************************************************************************


// ****************************************************************************************
//Timer with minimum time of 0.001 seconds ie 1ms, max time of 65sec
void delay_ms(uint16_t delayTime)
{
	//12MHz divided by 1024 is 11.718KHz, or clock time of 85.3micro seconds
	//multiplied by 12 gives 0.001024 seconds
	
	TCNT0 = 0x00;		//reset timer to 0
	OCR0 = 12;			//set compare register 
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
// ****************************************************************************************

// ****************************************************************************************
//Timer with minimum time of 1 second, max time of 18hours
void delay_sec(uint16_t delayTime)
{
	//delayTime = delayTime * 1000;
	//12MHz divided by 1024 is 11.718KHz, or clock time of 85.3micro seconds
	//multiplied by 11719 gives 1.00002 seconds
	
	TCNT1 = 0x0000;		//reset timer to 0
	OCR1A = 11719;			//set compare register 
	TIFR = (1<<OCF1A);	//reset compare flag
	
	uint16_t overflowCounter = 0;
	
	while (1)
	{
		while((TIFR & (1<<OCF1A))==0); //while OCF0, overflow flag is 0
		TCNT1 = 0x00;		//reset timer to 0
		TIFR = (1<<OCF1A); //reset compare flag
		overflowCounter++;
		if (overflowCounter >= delayTime)
		{
			return;
		}
	}	
}
// ****************************************************************************************