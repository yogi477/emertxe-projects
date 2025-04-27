

#include "main.h"
#include <xc.h>
void init_display(void)
{
    /*config portd as output*/
    TRISD = 0X00;
    /*config RA0,2,3,4 as */
    TRISA = TRISA & 0XF0;
    /*turn off the ssds*/
    PORTA = PORTA & 0XF0;
}

void display(unsigned char *ssd)
{
    unsigned char digit;
    for(digit = 0; digit < 4; digit++)
    {
        SSD_DATA_PORT = ssd[digit];
        SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0X01 << digit);
        for(unsigned int wait = 1000;wait--;);
    }
}