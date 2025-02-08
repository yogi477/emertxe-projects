#ifndef MAIN_H
#define	MAIN_H

void run_mode(void);

extern unsigned long int sec;
unsigned long int min = 0;
unsigned long int hour = 0;
unsigned char key;

void edit_mode(void);
unsigned int runflag = 0;
unsigned int f_flag = 0;

#endif	/* MAIN_H */

