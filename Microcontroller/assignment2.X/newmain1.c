#include"newfile.h"

void ledpattern1(void)
{      
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
          i = 0;
        }
}
void ledpattern2(void)
{      
        if(i<8)
        {
          LED_ARRAY = LED_ARRAY | (1<<(7-i));
          i++;
        }
        else if(i<16)
        {
           LED_ARRAY = LED_ARRAY >> 1; 
           i++;
        }
        else
        {
          i = 0;
        }
}
