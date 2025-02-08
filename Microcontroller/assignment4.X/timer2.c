#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
	
	TMR2ON = 1;
   
    
    //enabling prescaler
    T2CKPS1 = 0;
    T2CKPS0 = 0;
    
    PR2 = 250;
	
    /* Clearing timer2 overflow interrupt flag bit */
	TMR2IF = 0;

	/* Enabling timer2 overflow interrupt */
	TMR2IE = 1;
    
}
    