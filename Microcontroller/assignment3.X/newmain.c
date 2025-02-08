#include"newfile.h"
void init_config(void)
{
     LED_ARRAY_DDR = 0x00;
     KEY_PORT = 0x0F;
     KEY_PORT_DDR =  (KEY_PORT_DDR & 0x0F);
     LED_ARRAY = 0x00;
}
void main(void) {
    init_config();
    unsigned char key = KEY_PORT & INPUT_PINS;
    int flag = 0;
    while(1)
    {
        key = KEY_PORT & INPUT_PINS;
        if(key == SWITCH1)
        {
            i = 0,n = 0;
            LED_ARRAY = 0x00;
            flag = 1;
        }
        else if(key == SWITCH2)
        {
            i = 0;
            delay = 0;
            LED_ARRAY = 0x00;
            flag = 2;
            
        }
        else if(key == SWITCH3)
        {
            flag = 3;
            i = 0;
            delay = 0;
            LED_ARRAY = 0xAA;
        }
        else if(key == SWITCH4)
        {
            flag = 4;
            i = 0;
            delay = 0;
            LED_ARRAY = 0xF0;
        }
        
        if(delay++ == 20000)
        {
            delay = 0;
            if(flag == 1)
            {
                ledpattern1();
            }
            else if(flag == 2)
            {
                ledpattern2();
            }
            else if(flag == 3)
            {
                ledpattern3();
            }
            else if(flag == 4)
            {
                ledpattern4();
            }
        }
    }    
}

