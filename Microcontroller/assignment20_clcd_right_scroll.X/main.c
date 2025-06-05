#include <xc.h>
#include "clcd.h"

static void init_config(void)
{
    init_clcd();
  
}

void main(void)
{
    init_config();
    clcd_print("Right scrolling",LINE1(0));
    char str[] = "0123456789______";
    unsigned long  delay = 0;
    while (1)
    {
        if(delay++ == 1000)
        {
            delay = 0;
             right_scrolling(str);
        }
        clcd_print(str,LINE2(0));
    }
   
}