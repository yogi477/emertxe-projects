#include <xc.h>
#include "timer0.h"
#include "main.h"
#include"digital_keypad.h"

void init_config(void)
{
	PEIE = 1;
	/* Clear old content */
	PORTB = 0x00;

	/* Set PORTB as a Output */
	TRISB = 0x00;

	/* Config PORTB as digital */
	ADCON1 = 0x0F;

	init_timer0();

	GIE = 1;
   
}


void main(void)
{
	init_config();
    init_digital_keypad();
    unsigned char key;
    //LED1 = 1;
	while (1)
	{
		key = read_digital_keypad(STATE_CHANGE);
        
        if(program_cycle < duty_cycle)
                PORTB = 0xFF;
            else
                PORTB = 0x00;
        
            if(program_cycle++ == PERIOD)
                program_cycle = 0;
        
        if(key == SWITCH1)
        {
            TMR0ON = 1;
            duty_cycle = 100;
        }
            
	}
}
