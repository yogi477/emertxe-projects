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
    unsigned char key = (KEY_PORT & INPUT_PINS);
    int flag = 0;
    while(1)
    {
        key = (KEY_PORT & INPUT_PINS);
       if(key == DIR_SWITCH)
       {
           flag = !flag;
           //i = 0;
           delay = 0;
       }
       
       if(delay++ == 30000)
       {
           delay = 0;
           if(flag == 0)
           {
               ledpattern1();
           }
           else if(flag == 1)
           {
               ledpattern2();
           }
       }
       
    }
}
