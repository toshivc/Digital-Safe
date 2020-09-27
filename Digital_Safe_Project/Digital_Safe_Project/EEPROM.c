/*
 * EEPROM.c
 *
 * Created: 9/27/2020 8:29:55 PM
 *  Author: Ioanna & Toshi
 */ 

// Include file header
#include "EEPROM.h"
#include <avr/io.h>


// Variable definitions
char errorFlag = 0;

// Start functions
//****************************************************************************************
//Write to EEPROM
//Takes in the address of the location to write to, and the data to write into that address
//returns nothing(error code flag set?)

//do we need to use ware leveling(using multiple addresses so as not to damage EEPROM)
void write_EEPROM(uint8_t WriteData, uint16_t WriteAddress)
{
//should disable global interrupts here if we use them
	
	//check if address is valid
	if(WriteAddress > 0x400)	//only 2^10 = 1024 addresses
		{
			errorFlag =3;
			return;			//Set some debug flag?
		}
	
	
	//Wait till previous write operation is completed(i.e. wait till EEWE becomes zero).
	while(EECR & (1 << EEWE));	//b 0000 0010


	//Wait until SPMEN in SPMCR becomes zero		Dont think this step is necessary
	// only relevant if the software contains a boot loader allowing the CPU to program the Flash. If the Flash is never being updated by the CPU, can be omitted

	//Load the EEPROM address into EEAR at which the data has to be stored.
	//high and low registers, high register will always be 0 for us.
	EEAR = WriteAddress;

	//Load the data into EEDR which has to be stored in EEPROM.
	EEDR = WriteData;

	//Set the EEMWE (EEPROM Master Write Enable).
	asm("SBI 0x1C, 0x02");
	//set EEWE in EECR to 0			Dont think this step is necessary. Why is it listed?

	//Within four clock cycles after 4th step, set EEWE(Eeprom Write Enable) to 1 to trigger the EEPROM Write Operation
	asm("SBI 0x1C, 0x01");
return;
}
//****************************************************************************************

//****************************************************************************************
//Read EEPROM
uint8_t read_EEPROM(uint16_t readAddress)
{
	//check if address is valid
	if(readAddress > 0x400)	//only 2^10 = 1024 addresses
	{
		return 0;			//Set some debug flag?
	}
	
	//WAit for completion of previous Write operation.
	while(EECR & (1 << EEWE));

	//Load the EEPROM address into EEAR from where the data needs to be read.
	EEAR = readAddress;

	//Trigger the EEPROM read operation by setting EERE (EEPROM Read Enable).
	EECR |= (1 <<EERE);

	//Wait for some time (about 1ms) and collect the read data from EEDR.
	return EEDR;
}
//****************************************************************************************

//****************************************************************************************
//Store Passcode stores 4 bytes of passcode into memory location defined by the user.
//32 bit passcode must be divided into 4 bytes
//each byte is stored in location 0x00XY, where X is the hex value of the user, and Y is which byte is being stored
void storePasscode (unsigned long int Passcode, uint8_t user)
{
	//check if user input is valid
	switch(user){
		case 0x0A:
		case 0x0B:
		case 0x0C:
		case 0x0D:
		break;
		
		default:	//invalid user code		Set some debug flag here
		return;
	}
	
	//store each byte of passcode
	uint8_t passcodeByte[4];
	uint16_t passcodeAddress[4];
	
	for(int i = 0; i<4; i++)
	{
		//store each byte of passcode into an array
		passcodeByte[i] = Passcode>>(8*i);
		//define the location to store the passcode in EEPROM
		passcodeAddress[i]= (user<<4)|(4-i);
		//write the byte to the location in EEPROM
		write_EEPROM(passcodeByte[i],passcodeAddress[i]);
	}
	return;
}
//****************************************************************************************

//****************************************************************************************
//Reads the passcode from EEPROM and stores it into a long int
unsigned long int RecallPasscode(uint8_t user)
{
unsigned long int tempValue = 0;
unsigned long int passcode = 0;	
	for (int i = 0; i<4; i++)
	{
		//read the EEPROM value at location of user from LSB to MSB
		tempValue = read_EEPROM((user<<4)|(4-i));
		passcode |= tempValue<<(8*i);			//add each byte together to form a 4 byte passcode
	}
	return passcode;
}

//****************************************************************************************