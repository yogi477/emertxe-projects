#ifndef NEWFILE_H
#define	NEWFILE_H

#include<xc.h>
#define KEY_PORT PORTC
#define KRY_PORT_DDR TRISC

#define SSD_DATA_PORT			PORTD
#define SSD_CNT_PORT			PORTA
#define SSD_DATA_DDR            TRISD
#define SSD_CNT_DDR             TRISA

#define ZERO                0xE7
#define ONE                 0x21
#define TWO                 0xCB
#define THREE				0x6B
#define FOUR				0x2D
#define FIVE				0x6E
#define SIX                 0xEE
#define SEVEN				0x23
#define EIGHT				0xEF
#define NINE				0x6F
#define DOT                 0x10
#define BLANK				0x00

#define SWITCH1             RC0
#define INPUT_PINS          0x0F

void init_ssd_control(void);
void display(unsigned char data[]);
#endif	/* NEWFILE_H */

