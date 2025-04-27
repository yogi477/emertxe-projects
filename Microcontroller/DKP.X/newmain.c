#include"newfile.h"
void init_config(void)
{
    KEYPAD_PORT_DDR = (KEYPAD_PORT_DDR & 0xF0) | 0x0F;
    LED_ARRAY_DDR = 0x00;
    LED_ARRAY = 0x00;
}

void main(void) {
    init_config();
//    while(1)          //level triggering
//    {                 
//        if(RC0 == 0)
//        {
//            LED1 = !LED1;
//            for(unsigned long wait = 50000;wait--;);
//        }
//    }
    unsigned char once = 1;//edge triggering
    unsigned char once1 = 1;
    unsigned char once2 = 1;
    unsigned char once3 = 1;
    while(1)
    {
        if(RC0 == 0 && once)
        {
            once = 0;
            LED1 = !LED1;
        }
        else if(RC0 == 1)
            once = 1;
        
        //
        if(RC1 == 0 && once1)
        {
            once1 = 0;
            LED2 = !LED2;
        }
        else if(RC1 == 1)
            once1 = 1;
        //
        if(RC2 == 0 && once2)
        {
            once2 = 0;
            LED3 = !LED3;
        }
        else if(RC2 == 1)
            once2 = 1;
        //
        if(RC3 == 0 && once3)
        {
            once3 = 0;
            LED4 = !LED4;
        }
        else if(RC3 == 1)
            once3 = 1;
    }

}
