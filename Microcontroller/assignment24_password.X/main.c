#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"

void init_config(void)
{
	init_matrix_keypad();
	init_clcd();
}

void main(void)
{
	init_config();
    unsigned char key;
	unsigned int i = 0;
    char original_pass[] = "10101010";
    char user_pass[9];
    unsigned int count = 5;
    unsigned long delay = 0;
    unsigned int flag = 0;
    unsigned long delay1 = 0;
    LED = 0;
	while(1)
	{
		if(count < 5 && count > 0)
        {
            if(delay++ == (count * 200))
            {
                delay = 0;
                LED = !LED;
            }
        }
        key = read_switches(STATE_CHANGE);
        clcd_print(" ENTER PASSWORD ", LINE1(0));
        if(delay1++ == 400)
        {
            clcd_putch('_',LINE2(i));
        }
        else if(delay1++ == 800)
        {
            delay1 = 0;
            clcd_putch(' ',LINE2(i));
        }
        if(i<8)
        {
           if(key == MK_SW1)
           {
               clcd_putch('*',0xC0 + i);
               user_pass[i] = '1';
               i++;
           }
           if(key == MK_SW2)
           {
               clcd_putch('*',0xC0 + i);
               user_pass[i] = '0';
               i++; 
           }
        }
        else if(i==8)
        {
            delay = 0;
            flag = 0;
            CLEAR_DISP_SCREEN;
            clcd_print(original_pass,LINE1(0));
            clcd_print(user_pass,LINE2(0));
//            while(1);
            original_pass[8] = '\0';
            user_pass[8] = '\0';
            for(int j=0;j<8;j++)
            {
                if(original_pass[j] != user_pass[j])
                {
                   flag = 1;
                   count--;
                    break;
                }
            }
            if(flag == 0)
            {
                CLEAR_DISP_SCREEN;
                clcd_print(" SUCCESS ", LINE1(0));
                clcd_print(" YOGESH K ", LINE2(0));
                while(1);
            }
            if (count != 0)
            {
                CLEAR_DISP_SCREEN;
                clcd_print(" WRONG PASSWORD ", LINE1(0));
                clcd_print("Attempts left: ",LINE2(0));
                clcd_putch(count + 48,LINE2(14));
                for(unsigned long int k = 500000;k--;);
                CLEAR_DISP_SCREEN;
                i = 0;
            }
            else
            {
                CLEAR_DISP_SCREEN;
                clcd_print("Attempt are over",LINE1(0));
                clcd_print("RESET",LINE2(5));
                while(1);
            }
        }
    }
}
    
