#include"newfile.h"
static unsigned char ssd[4];
static unsigned char digit[] = {ZERO,ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,UNDER_SCORE,UNDER_SCORE};
unsigned int i = 0,j = 1,k = 2,l=3;
void init_config(void)
{
	init_ssd_control();
}

void main(void)
{
	init_config();
	unsigned long delay = 0;
    while(1)
	{
       
        if(delay++ == 100)
        {    
            delay = 0;
            if(i++ == 11)
            {
                i = 0;
            }
//            if(i<11)
//            {
//                i++;
//            }
//            else
//            {
//                i = 0;
//            }
//            if(i<11)
//            {
//                
//                i++;
//            }
//            else
//            {
//                i = 0;
//            }
//            if(i<11)
//            {
//                
//                i++;
//            }
//            else
//            {
//                i = 0;
//            }
//            if(i<11)
//            {
//               
//                i++;
//            }
//            else
//            {
//                i = 0;
//            }
        }
        ssd[0] = digit[i%12];
		ssd[1] = digit[(i+1)%12];
		ssd[2] = digit[(i+2)%12];
		ssd[3] = digit[(i+3)%12];
        display(ssd); 
	}
    	
}