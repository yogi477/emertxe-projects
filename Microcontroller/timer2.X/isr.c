#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR2IF)
	{
		if (count++ == 5000)
		{
			count = 0;
			LED1 = !LED1;
		}
		TMR2IF = 0;
	}
}