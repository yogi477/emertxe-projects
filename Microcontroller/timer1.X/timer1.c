#include <xc.h>
#include "timer1.h"
void init_timer1(void)
{
	
	TMR1ON = 1;
    T1RD16 = 0;
    TMR1CS = 0;
    T1OSCEN = 0;
    TMR1 = 3036;
    
    //enabling prescaler
    T1CKPS1 = 0;
    T1CKPS0 = 0;
    
	
    /* Clearing timer1 overflow interrupt flag bit */
	TMR1IF = 0;

	/* Enabling timer1 overflow interrupt */
	TMR1IE = 1;
    
}
    