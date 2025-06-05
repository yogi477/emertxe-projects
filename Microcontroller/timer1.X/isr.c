#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR1IF)
	{
		TMR1 = TMR1 + 3036;
        if (count++ == 120) // for 1.5 sec
		{
			count = 0;
			LED1 = !LED1;
		}
		TMR1IF = 0;
	}
}