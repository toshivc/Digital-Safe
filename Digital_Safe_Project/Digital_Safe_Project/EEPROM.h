/*
 * EEPROM.h
 *
 * Created: 9/27/2020 8:25:37 PM
 *  Author: Ioanna & Toshi
 */ 

// Include guards for safety (needed for every header file)
#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

// Define variables
extern char errorFlag;

// Function Prototypes (within the EEPROM.c file)
void write_EEPROM(unsigned char WriteData, unsigned int WriteAddress);
unsigned char read_EEPROM(unsigned int readAddress);


#endif /* EEPROM_H_ */