#include <xc.h>
#include "main.h"
#include "ssd.h"
#include"keypad.h"
#include"timer0.h"
static unsigned char ssd[MAX_SSD_CNT];
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
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
    
    init_ssd_control();
    init_digital_keypad();
}
void main(void)
{
	init_config();
    unsigned long delay = 0;
	while(1)
	{
        key = read_digital_keypad(STATE_CHANGE);
        if(key == SWITCH4)
        {
            runflag = !runflag;
            TMR0ON = !TMR0ON;
            sec = 0;
        }
        if(runflag == 1)
        {
            //editmode
            edit_mode();
            if(f_flag == 0)
            {
                if(delay++ == 100)
                {
                    ssd[0] = digit[hour/10];
                    ssd[1] = digit[hour%10];
                }
                else if(delay == 200)
                {
                    delay = 0;
                    ssd[0] = BLANK;
                    ssd[1] = BLANK;
                }
              ssd[2] = digit[min/10];
              ssd[3] = digit[min%10];
            }
            else if(f_flag == 1)
            {
                if(delay++ == 100)
                {
                     ssd[2] = digit[min/10];
                     ssd[3] = digit[min%10];
                }
                else if(delay == 200)
                {
                    delay = 0;
                    ssd[2] = BLANK;
                    ssd[3] = BLANK;
                }
             
                    ssd[0] = digit[hour/10];
                    ssd[1] = digit[hour%10];
            }
            
        }
        else if(runflag == 0)
        {
            run_mode();
            if(sec % 2 == 0)
            {
             ssd[0] = digit[hour/10];
             ssd[1] = digit[hour%10] | DOT;
             ssd[2] = digit[min/10];
             ssd[3] = digit[min%10];
            }
            else
            {
              ssd[0] = digit[hour/10];
              ssd[1] = digit[hour%10];
              ssd[2] = digit[min/10];
              ssd[3] = digit[min%10];
            }
        }
            
		display(ssd);
	}
}