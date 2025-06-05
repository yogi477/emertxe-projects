#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned long int count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 100000)
		{
			count = 0;
			TMR0ON = 0;
            duty_cycle = 10;
        }
            TMR0IF = 0;
	}
}