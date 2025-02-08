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