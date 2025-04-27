#include <xc.h>
#include "main.h"

void __interrupt() isr(void) {
    static unsigned short count;

    if (TMR0IF) {
        TMR0 = TMR0 + 8;

        if (timer_cycle++ == PERIOD)
            timer_cycle = 0;

        TMR0IF = 0;
    }
}