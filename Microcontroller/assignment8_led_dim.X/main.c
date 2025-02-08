#include "main.h"
#include "adc.h"
#include"timer0.h"
#include <xc.h>

static void init_config(void)
{
	LED = 0;

	TRISB = 0;

    init_adc();
    init_timer0();
}

void main(void)
{
    unsigned short adc_reg_val;

    init_config();

    while (1)
    {
        adc_reg_val = read_adc(CHANNEL4);
        duty_cycle = adc_reg_val/10;
        
        if(timer_cycle < duty_cycle)
            LED = 0xFF;
        else
            LED = 0x00;
    }
}













