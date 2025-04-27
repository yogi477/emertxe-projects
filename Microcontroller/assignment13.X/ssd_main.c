#include"newfile.h"

void init_ssd_control(void)
{
	/* Setting PORTB as output for Data Lines */
	TRISD = 0x00;
	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CNT_PORT = SSD_CNT_PORT & 0xF0;
    
    TRISC = TRISC & 0x01;
    
}

/* Better if implemented in timer handler */
void display(unsigned char data[])
{
	unsigned long wait;
	unsigned char data_bit;
	unsigned char digit;

	for (digit = 0; digit <= 4; digit++)
	{
		SSD_DATA_PORT = data[digit];
		SSD_CNT_PORT = (SSD_CNT_PORT & 0xF0) | (0x01 << digit);

		for (wait = 1000; wait--; );
	}
}
