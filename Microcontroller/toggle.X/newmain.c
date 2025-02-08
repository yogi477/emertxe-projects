#include"newfile.h"
//unsigned char *portb = 0xF81,*trisb = 0xF93;
void intt_config(void)
{
    LED_ARRAY_DDR = 0x00;
}
void main(void)
{
    intt_config();
    unsigned long delay = 0;
    while(1)
    {
        //for(unsigned long wait=500000;wait--;);
//        if(delay <= 50000)
//        {
//           LED_ARRAY = 0x01;
//           i++;
//        }
//        else if(delay > 50000 && delay<=100000)
//        {
//           LED_ARRAY = 0x00;
//           i++;
//        }
//        if(delay > 100000)
//        {
//            i = 0;
//        }
        //for(unsigned long wait=500000;wait--;);
        
        if(delay++ == 50000)
            LED_ARRAY = 0x01;
        else if(delay == 100000)
        {
            LED_ARRAY = 0x00;
            delay = 0;
            
        }
    }
}