#include"main.h"
#define PERIOD 100
unsigned long int duty_cycle = 20,program_cycle;
void init_config(void)
{
    LED_ARRAY_DDR = 0x00;
    LED_ARRAY = 0x00;
    RB1 = 1;
}
void software_pwm(void)
{
    if(program_cycle < duty_cycle)
        RB0 = 1;
    else
        RB0 = 0;
    if(program_cycle++ == PERIOD)
        program_cycle = 0;
}
void main(void) {
    
    init_config();
    while(1)
    {
//        RB0 = 1;
//        for(unsigned long wait = 900;wait--;);
//        RB0 = 0;
//        for(unsigned long wait = 100;wait--;);
        software_pwm();
        for(unsigned long wait = 50000;wait--;);
        for(unsigned long wait = 50000;wait--;);
        for(unsigned long wait = 50000;wait--;);
        for(unsigned long wait = 50000;wait--;);
    }
}
