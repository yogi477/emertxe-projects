#ifndef NEWFILE_H
#define	NEWFILE_H

#include<xc.h>
#define LED_ARRAY       PORTB
#define LED_ARRAY_DDR   TRISB

#define KEY_PORT		PORTC 
#define KEY_PORT_DDR    TRISC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07

#define INPUT_PINS              0x0F

unsigned long delay = 0;
unsigned long  i = 0,n = 0;

void ledpattern1(void);
void ledpattern2(void);
void ledpattern3(void);
void ledpattern4(void);
#endif	/* NEWFILE_H */

