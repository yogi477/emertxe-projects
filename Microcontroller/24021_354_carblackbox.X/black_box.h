#ifndef BLACK_BOX_H
#define	BLACK_BOX_H

#include <xc.h>
#include"adc.h"
#include"clcd.h"
#include"matrix_keypad.h"
#include"i2c.h"
#include"external_eeprom.h"
#include"ds1307_1.h"
#include"uart.h"
/* Enum for maintaining the app state */
typedef enum {
    e_dashboard, e_main_menu, e_view_log, e_set_time, e_download_log, e_clear_log
} State_t;


extern State_t state; // App state
unsigned char key; //
unsigned char gears[9][3] = {"ON","GN","G1","G2","G3","G4","G5","GR","C "};
unsigned short gear_index = 0;
unsigned short adc_val;
unsigned char read_adr = 0x00;
unsigned char write_adr = 0x00;
short count = 0;
unsigned char disp_menu[4][13] = {"View log","Clear log","Download log","Set time"};
unsigned short disp_index = 0;
short count1 = 0;
unsigned char clock_reg[3];
unsigned char calender_reg[4];
unsigned char time[9];
unsigned char date[11];
short menu_cnt = 0;
char str[18];

//Function declarations

//Dashboard function declaration
void view_dashboard(void);

//Storing events function declaration
void event_store(unsigned char time[],unsigned char gear[],int speed);

//Password function declaration
void password(void);

//main menu function declaration
void display_main_menu(void);

//View log function declaration
void view_log(void);

//Reading events function declaration
void event_reader(void);

//Change password function declaration
void change_password(void);

//Set time function declaration
void set_time(void);

//Download log function _decleration
void download_log(void);

//Clear log function declaration
void clear_log(void);

void event_read(void);

static void get_time(void);
#endif	/* BLACK_BOX_H */

