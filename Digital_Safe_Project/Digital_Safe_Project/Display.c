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

//****************************************************************************************
// Convert binary value to more realistic LED representation
uint8_t displayKeys(uint8_t keyValue)
{
	switch(keyValue)
	{
		case 0x00:
		return 0x00;
		break;
		
		case 0x01:
		return 0x01;
		break;
		
		case 0x02:
		return 0x02;
		break;
		
		case 0x03:
		return 0x04;
		break;
		
		case 0x04:
		return 0x08;
		break;
		
		case 0x05:
		return 0x10;
		break;
		
		case 0x06:
		return 0x20;
		break;
		
		case 0x07:
		return 0x40;
		break;
		
		case 0x08:
		return 0x80;
		break;
		
		case 0x09:	
		return 0x81;
		break;
		
		case 0x10:
		return 0x10;
		break;
		
		case 0x0A:
		return 0x0A;
		break;
		
		case 0x0B:
		return 0x0B;
		break;
		
		case 0x0C:
		return 0x0C;
		break;
		
		case 0x0D:
		return 0x0D;
		break;
		
		default:
		return 0;
		
	}
	 
}