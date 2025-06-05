#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if(timer_cycle < duty_cycle)
            RB0 = 1;
        else
            RB0 = 0;
        
        if(timer_cycle++ == PERIOD)
            timer_cycle = 0;
		
        TMR0IF = 0;
	}
}