#include "main.h"
#include "adc.h"
#include"clcd_.h"
#include <xc.h>

static void init_config(void)
{
	init_adc();
}

void main(void)
{
    unsigned short adc_reg_val;
    char str[5];
    init_config();
    init_clcd();

    while (1)
    {
        adc_reg_val = read_adc(CHANNEL6);
        int_to_str(adc_reg_val, str);
        clcd_print("Temperature",LINE1(1));
        clcd_print(str,LINE2(5));
        clcd_putch('C', LINE2(7));
    }
}













