#include"newfile.h"
static unsigned char ssd[4];
static unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
static unsigned count = 0;
unsigned int delay = 0;
unsigned int i = 0;

void main(void) {
    
    init_ssd_control();
    while(1)
    {
        ssd[3] = digit[count % 10];
        ssd[2] = digit[(count/10) %10];
        ssd[1] = digit[(count/100) %10];
        ssd[0] = digit[(count/1000) %10];
          
        if(SWITCH1 == 0)
            {
                i++;
                if(i>150)
                {
                    count = 0;
                }
            }
            else if(i>1 && i < 50)
            {
                count++;
                i = 0;
               
            }
            else
                i = 0;
        display(ssd);  
        
    }
}
