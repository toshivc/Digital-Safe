/*
 * EEPROM.h
 *
 * Created: 9/27/2020 8:25:37 PM
 *  Author: Ioanna & Toshi
 */ 

#include <avr/io.h>

// Include guards for safety (needed for every header file)
#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

// Define variables


// Function Prototypes (within the EEPROM.c file)
void write_EEPROM(uint8_t WriteData, uint16_t WriteAddress);
uint8_t read_EEPROM(uint16_t readAddress);
unsigned long int RecallPasscode(uint8_t user);
void storePasscode (unsigned long int Passcode, uint8_t user);


#endif /* EEPROM_H_ */