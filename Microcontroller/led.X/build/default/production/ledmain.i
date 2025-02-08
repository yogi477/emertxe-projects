# 1 "ledmain.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "ledmain.c" 2
unsigned char *portb = 0xF81,*trisb = 0xF93;
void intt_config(void)
{
    *trisb = 0x00;
}
void main(void)
{
    intt_config();
    *portb = 0x00;
    while(1)
    {
        for(int i=0;i<8;i++)
        {
            for(unsigned long wait=100000;wait--;);
            *portb = *portb | (1<<i);

        }
        for(int i=0;i<8;i++)
        {
            for(unsigned long wait=100000;wait--;);
            *portb = *portb & ~(1<<i);

        }

    }
}
