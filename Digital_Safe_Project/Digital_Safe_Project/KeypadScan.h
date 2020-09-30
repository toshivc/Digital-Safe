/*
 * KeypadScan.h
 *
 * Created: 9/28/2020 2:49:07 PM
 *  Author: Toshi & Ioanna
 */ 


#ifndef KEYPADSCAN_H_
#define KEYPADSCAN_H_

// Variables relevant to keypad scan
//extern unsigned char key;
//extern unsigned char portCValue;			//defining these variables here means they are defined twice
//extern unsigned char KeyPressed;
//extern const char col[4];
//extern unsigned char Keys[16];


// Function prototypes for function within KeypadScan.c
unsigned char ReadOne();
unsigned long int InputPasscode (void);
void ReadNone (void);


#endif /* KEYPADSCAN_H_ */