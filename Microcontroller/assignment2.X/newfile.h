#ifndef NEWFILE_H
#define	NEWFILE_H

#include<xc.h>
#define LED_ARRAY PORTB
#define LED_ARRAY_DDR TRISB

#define KEY_PORT PORTC
#define KEY_PORT_DDR TRISC

#define DIR_SWITCH 0x0E
#define INPUT_PINS 0x0F

unsigned long delay = 0;
unsigned long i = 0;

void ledpattern1(void);
void ledpattern2(void);

#endif	/* NEWFILE_H */

