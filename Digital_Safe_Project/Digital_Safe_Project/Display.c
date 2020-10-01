/*
 * Display.c
 *
 * Created: 27/09/2020 11:34:34 PM
 *  Author: Toshi_2
 */ 
#include <avr/io.h>
#include "Delay.h"


//unlock LED sequence
void displayUnlock (void)
{
	for (int i = 0; i <4; i++)
	{
		PORTB = 1<<(1+i*2);
		delay_ms(100);
	}
	for (int i = 0; i <4; i++)
	{
		PORTB = 1<<(7-i*2);
		delay_ms(100);
	}
	PORTB = 0x00;
}
//****************************************************************************************

//****************************************************************************************
//unlock LED sequence
void displayLock (void)
{
	for (int i = 0; i <4; i++)
	{
		PORTB = 1<<(i*2);
		delay_ms(100);
	}
	for (int i = 0; i <4; i++)
	{
		PORTB = 1<<(8-i*2);
		delay_ms(100);
	}
	PORTB = 0x00;
}
//****************************************************************************************

//****************************************************************************************
//Programming mode LED sequence
void displayProgramming(void)
{
	for (int i = 0; i <10; i++)
	{
		PORTB = 0xFF;
		delay_ms(100);
		PORTB = 0x00;
		delay_ms(100);
	}
}
//****************************************************************************************

//****************************************************************************************
//Programming mode LED sequence
void displayIncorrect(void)
{
	for (int i = 0; i <4; i++)
	{
		PORTB = 0x55;
		delay_ms(80);
		PORTB = 0x00;
		delay_ms(80);
	}
}
//****************************************************************************************