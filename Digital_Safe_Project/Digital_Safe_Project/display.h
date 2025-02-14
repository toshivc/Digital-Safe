/*
 * display.h
 *
 * Created: 27/09/2020 11:35:05 PM
 *  Author: Toshi_2
 */ 

#include <avr/io.h>

#ifndef DISPLAY_H_
#define DISPLAY_H_

// Define Extern variables

// Function Prototypes (within the Display.c file)
void displayUnlock (void);
void displayLock (void);
void displayProgramming(void);
void displayIncorrect(void);
uint8_t displayKeys(uint8_t keyValue);
void displayLockout(void);
void displayUser(uint8_t user);
void displayUnlockProg(void);


#endif /* DISPLAY_H_ */