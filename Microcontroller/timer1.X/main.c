#include <xc.h>
#include "timer1.h"
#include "main.h"
#include"isr.h"
void init_config(void)
{
	PEIE = 1;
	/* Clear old content */
	PORTB = 0x00;

	/* Set PORTB as a Output */
	TRISB = 0x00;

	/* Config PORTB as digital */
	ADCON1 = 0x0F;

	init_timer1();

	GIE = 1;
}


void main(void)
{
	init_config();

	while (1)
	{
		;
	}
}
