#include"newfile.h"
void init_config(void)
{
    LED_ARRAY = 0x00;
    LED_ARRAY_DDR = 0x00;
}
void main(void) {
    init_config();
    unsigned long i = 0;
    unsigned long delay = 0;
    unsigned long n = 0;
    while(1)
    {
        if(delay++ == 50000)
        {
            delay = 0;
            if(i<8)
            {
                LED_ARRAY = LED_ARRAY | (1<<i);
                i++;
            }
            else if(i<16)
            {
                LED_ARRAY = LED_ARRAY << 1;
                i++;
            }
            else
            {
                
                if(n<8)
                {
                    LED_ARRAY = LED_ARRAY | (1<<(7-n));
                    n++;
                }
                else if(n<16)
                {
                    LED_ARRAY = LED_ARRAY >> 1;
                    n++;
                }
                else
                {
                    n = 0;
                    i = 0;
                }
                
            }
            
            
        }
           
    }
}
