/*
 * Digital_Safe_Project.c
 *
 * Created: 9/24/2020 11:57:08 AM
 * Author : yoyos
 */ 


#define _EEWE 1
#define _EEMWE 2
#define _EERE 0

volatile unsigned char * _EECR = (unsigned char *)0x3c;
volatile unsigned int * _EEAR = (unsigned int *)0x3e;
volatile unsigned char * _EEDR = (unsigned char *)0x3d;


//global error flag
unsigned char errorFlag = 0;

//function prototypes
void write_EEPROM(unsigned char WriteData, unsigned int WriteAddress);
unsigned char read_EEPROM(unsigned int readAddress);

int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
	
		//hello test one two mic check one tawooo oonee tawwwooo
    }
}

//


//****************************************************************************************
//write EEPROM
//Takes in the address of the location to write to, and the value to write to that address
//returns nothing(error code flag set?)

//do we need to use ware leveling(using multiple addresses so as not to damage EEPROM)
void write_EEPROM(unsigned char WriteData, unsigned int WriteAddress)
{
//should disable global interrupts here if we use them
	
	//check if address is valid
	if(WriteAddress > 0x400)	//only 2^10 = 1024 addresses
		{
			errorFlag =3;
			return;			//Set some debug flag?
		}
	
	
	//Wait till previous write operation is completed(i.e. wait till EEWE becomes zero).
	while(*_EECR & (1<<_EEWE));	//b 0000 0010


	//Wait until SPMEN in SPMCR becomes zero		Dont think this step is necessary
	// only relevant if the software contains a boot loader allowing the CPU to program the Flash. If the Flash is never being updated by the CPU, can be omitted

	//Load the EEPROM address into EEAR at which the data has to be stored.
	//high and low registers, high register will always be 0 for us.
	*_EEAR = WriteAddress;

	//Load the data into EEDR which has to be stored in EEPROM.
	*_EEDR = WriteData;

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
unsigned char read_EEPROM(unsigned int readAddress)
{
	//check if address is valid
	if(readAddress > 0x400)	//only 2^10 = 1024 addresses
	{
		return;			//Set some debug flag?
	}
	
	//WAit for completion of previous Write operation.
	while(*_EECR & (1<<_EEWE));

	//Load the EEPROM address into EEAR from where the data needs to be read.
	*_EEAR = readAddress;

	//Trigger the EEPROM read operation by setting EERE (EEPROM Read Enable).
	*_EECR |= (1<<_EERE);

	//Wait for some time (about 1ms) and collect the read data from EEDR.
	return *_EEDR;
}
//****************************************************************************************