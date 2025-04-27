# 1 "ssd_modes.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ssd_modes.c" 2
# 1 "./main.h" 1



void run_mode(void);

extern unsigned long int sec;
unsigned long int min = 0;
unsigned long int hour = 0;
unsigned char key;

void edit_mode(void);
unsigned int runflag = 0;
unsigned int f_flag = 0;
# 1 "ssd_modes.c" 2

# 1 "./keypad.h" 1
# 17 "./keypad.h"
void init_digital_keypad(void);
unsigned char read_digital_keypad(unsigned char detection_type);
# 2 "ssd_modes.c" 2

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
    if(key == 0x0B)
    {
        f_flag = !f_flag;
    }
    if(key == 0x0E)
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
    if(key == 0x0D)
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
