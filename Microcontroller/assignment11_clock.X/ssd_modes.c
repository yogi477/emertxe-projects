#include"main.h"
#include"keypad.h"
void run_mode(void) {
    
        if(sec == 59)
        {
            sec = 0;
            if(min++ == 59)
            {
                min = 0;
                if(hour++ == 23)
                    hour = 0;
            }
        }
}
void edit_mode(void)
{
    if(key == SWITCH3)
    {
        f_flag = !f_flag;
    }
    if(key == SWITCH1)
    {
        if(f_flag == 0)
        {
            if(hour++ == 23)
                hour = 0;
        }
        else if(f_flag == 1)
        {
            if(min++ == 59)
                min = 0;
        }
    }
    if(key == SWITCH2)
    {
        if(f_flag == 0)
        {
            if(hour-- == 0)
                hour = 23;
        }
        else if(f_flag == 1)
        {
            if(min-- == 0)
                min = 59;
        }
    }
}
