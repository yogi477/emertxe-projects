#include <xc.h>
#include "timer2.h"

void init_timer2(void)
{
	
	TMR2ON = 1;
   
    
    //enabling prescaler
    T2CKPS1 = 0;
    T2CKPS0 = 1;
    
    PR2 = 249;
	
    /* Clearing timer2 overflow interrupt flag bit */
	TMR2IF = 0;

	/* Enabling timer2 overflow interrupt */
	TMR2IE = 1;
    
}
    