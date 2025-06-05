
#include "main.h"
#include "eeprom.h"

#include <xc.h>
static unsigned int i;
void int_config(void)
{
    ADCON1 = 0x0F;
    init_digital_keypad();
    init_display();
}
    void main() {
        static unsigned char ssd[MAX_SSD_CNT];
        static unsigned char digit[] = {ZER, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
        int_config();
        unsigned char key;
        static unsigned char delay = 0;
        int flag = 0;
        i = read_internal_eeprom(COUNT_ADDR);
 
    while (1) {
        key = read_digital_keypad(LEVEL);
        if(key == SWITCH2)
        {
            write_internal_eeprom(COUNT_ADDR,i); 
        }
        
        if (key == SWITCH1) {

            if (delay++ == 200) {
                i = 0;
                flag = 1; 
                delay = 0;
            }
        }
        else if (delay > 0 && delay < 200) {
            if (flag == 0)
                i++;
            else
                flag = 0;
            delay = 0;
        }
       
        ssd[3] = digit[i % 10];
        ssd[2] = digit[(i % 100) / 10];
        ssd[1] = digit[(i % 1000) / 100];
        ssd[0] = digit[i / 1000];
        display(ssd);

    }
    return;
}

