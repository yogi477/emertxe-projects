#ifndef MAIN_H
#define MAIN_H

/* The name LED1 is based on the legend in eCee Board */
#define LED1					PORTBbits.RB0
#define ON					1
#define OFF					0
#define PERIOD 100
unsigned long int duty_cycle = 10,program_cycle;

#endif