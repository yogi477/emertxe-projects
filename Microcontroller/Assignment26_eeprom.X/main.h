#define LEVEL					     	0
#define STATE_CHANGE			       	1

#define KEY_PORT					PORTC

#define SWITCH1					0x0E
#define SWITCH2					0x0D
#define SWITCH3					0x0B
#define SWITCH4					0x07
#define ALL_RELEASED					0x0F

#define INPUT_PINS					0x0F
#define COUNT_ADDR            0x00
#define MAX_SSD_CNT         4
#define MAX_COUNT           9
#define ADD               0x00

void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);

#ifndef SSD_H
#define SSD_H
void init_display(void);
void display(unsigned char *ssd);

#define SSD_DATA_PORT PORTD
#define SSD_CNT_PORT PORTA

/* This values are for common cathode display */
#define ZER				0xE7
#define ONE				0x21
#define TWO				0xCB
#define THREE				0x6B
#define FOUR				0x2D
#define FIVE				0x6E
#define SIX				0xEE
#define SEVEN				0x23
#define EIGHT				0xEF
#define NINE				0x6F
#define DOT				0x10
#define BLANK				0x00
#endif
