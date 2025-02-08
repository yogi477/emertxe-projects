
#include"black_box.h"
short event_cnt = 0, extra_count = 0;
short num_cnt = 0;

void view_dashboard(void) {
    //read adc value
    get_time();
    if (key == MK_SW1) {
        if (gear_index < 7) {
            gear_index++;
            event_store(time, gears[gear_index], adc_val);

        } else if (gear_index == 7)
            gear_index = 7;
        else
            gear_index = 1;
    } else if (key == MK_SW2) {
        if (gear_index > 1 && gear_index < 8) {
            gear_index--;
            event_store(time, gears[gear_index], adc_val);

        } else
            gear_index = 1;
    } else if (key == MK_SW3) {
        gear_index = 8;
    } else if (key == MK_SW11) {
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        return;

    }
    if (adc_val > 99) {
        adc_val = 99;
    }
    clcd_print("Time", LINE1(2));
    clcd_print(time, LINE2(0));
    clcd_print("GEAR", LINE1(9));
    clcd_print(gears[gear_index], LINE2(9));
    //clcd_print("Time",LINE1(0));a6 
    clcd_print("SP", LINE1(14));
    clcd_putch((adc_val / 10) + 48, LINE2(14));
    clcd_putch((adc_val % 10) + 48, LINE2(15));



}

void event_store(unsigned char time[], unsigned char gear[], int speed) {
    //time
    for (int i = 0; i < 8; i++) {
        if (i == 2 || i == 5)
            continue;
        else {
            write_external_eeprom(write_adr++, time[i]);
        }
    }
    //gear
    write_external_eeprom(write_adr++, gear[0]);
    write_external_eeprom(write_adr++, gear[1]);
    //speed
    write_external_eeprom(write_adr++, ((speed / 10) + 48));
    write_external_eeprom(write_adr++, ((speed % 10) + 48));

    
    if (event_cnt++ == 10) 
    {
        event_cnt = 10;
    } else {
        if (extra_count++ == 9)
            extra_count = 0;
    }
    if (write_adr == 99)
        write_adr = 0x00;
    //    if(event_cnt == 10)
    //    {
    //        event_cnt = 10;
    //    }
    //    else 
    //    {
    //        
    //    }



}

void event_read(void) {
    //time
    CLEAR_DISP_SCREEN;
    for (int i = 0; i < 14; i++) {

        if (i == 2 || i == 5) {
            str[i] = ':';
        } else if (i == 8 || i == 11) {
            str[i] = ' ';
        } else {
            str[i] = read_external_eeprom(read_adr++);
        }

    }
    if (read_adr == 99)
        read_adr = 0x00;
    str[14] = '\0';
    clcd_print(str, LINE2(2));
    //for(unsigned long wait = 1000000;wait--;);
}

void view_log(void) {
    if (event_cnt == 0) {

        clcd_print("NO LOGS", LINE1(0));
        clcd_print("TO DISPLAY", LINE2(5));
        for (unsigned long wait = 500000; wait--;);
        CLEAR_DISP_SCREEN;
        state = e_main_menu;

    } else {
        //CLEAR_DISP_SCREEN;
        clcd_print("#", LINE1(0));
        clcd_print("Time", LINE1(3));
        clcd_print("GR", LINE1(11));
        clcd_print("SP", LINE1(14));
        clcd_putch(num_cnt + 48, LINE2(0));
        static once = 1;
        if (once) {
            read_adr = extra_count * 10;
            event_read();
            once = 0;
        }

        if (key == MK_SW1 && (count1 < event_cnt - 1)) {
            event_read();
            count1++;
            num_cnt++;
        }
        else if (key == MK_SW2 && (count1 > 0)) {
            read_adr = read_adr - 20;
            if (read_adr <= 0) {
                read_adr = 0;
            }
            event_read();
            count1--;
            num_cnt--;
        } else if (key == MK_SW12) {
            CLEAR_DISP_SCREEN;
            once = 1;
            read_adr = 0x00;
            write_adr = 0x00;
            num_cnt = 0;
            count1 = 0;
            state = e_main_menu;
        }
    }

}

static void get_time(void) {
    clock_reg[0] = read_ds1307(HOUR_ADDR);
    clock_reg[1] = read_ds1307(MIN_ADDR);
    clock_reg[2] = read_ds1307(SEC_ADDR);

    if (clock_reg[0] & 0x40) {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    } else {
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    time[2] = ':';
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':';
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0';
}

void clear_log(void) {
    event_cnt = 0;
    write_adr = 0x00;
    extra_count = 0x00;
    clcd_print("LOGS", LINE1(0));
    clcd_print("CLEARED", LINE2(5));
    for (unsigned long wait = 500000; wait--;);
    CLEAR_DISP_SCREEN;
    state = e_main_menu;
}

void download_log(void) {
    short cnt = 0;

    if (event_cnt == 0) {
        clcd_print("NO LOGS", LINE1(0));
        clcd_print("TO DOWNLOAD", LINE2(3));
        for (unsigned long wait = 500000; wait--;);
        CLEAR_DISP_SCREEN;
        puts("No Logs to Download");
        puts("\n\r");
        state = e_main_menu;
    } else {
        clcd_print("DOWNLOADED.", LINE1(4));
        for (unsigned long wait = 500000; wait--;);
        CLEAR_DISP_SCREEN;
        puts("NO TIME   GEAR SP");
        puts("\n\r");
        read_adr = extra_count * 10;
        while (cnt < event_cnt) {
            putch(cnt + 48);
            putch(' ');
            event_read();
            puts(str);
            puts("\n\r");
            cnt++;
        }
        CLEAR_DISP_SCREEN;
        state = e_main_menu;
        read_adr = 0x00;
        write_adr = 0x00;
        cnt = 0;
    }
}

void set_time(void) {
    static short hour = 0, min = 0, sec = 0;
    static short f_flag = 0;
    static unsigned long delay = 0;

    hour = ((time[0] - '0') * 10) + (time[1] - '0');
    min = ((time[3] - '0') * 10) + (time[4] - '0');
    sec = ((time[6] - '0') * 10) + (time[7] - '0');

    clcd_print("HH:MM:SS", LINE1(3));

    if (key == MK_SW2) {
        f_flag = (f_flag + 1) % 3;  
    } else if (key == MK_SW1) {
        if (f_flag == 0) {
            hour = (hour + 1) % 24;
        } else if (f_flag == 1) {
            min = (min + 1) % 60;
        } else if (f_flag == 2) {
            sec = (sec + 1) % 60;
        }
    } else if (key == MK_SW12) {
        unsigned data = 0;
        write_ds1307(SEC_ADDR, data | 0x80); // Halt RTC

        write_ds1307(HOUR_ADDR, ((hour / 10) << 4) | (hour % 10));
        write_ds1307(MIN_ADDR, ((min / 10) << 4) | (min % 10));
        write_ds1307(SEC_ADDR, ((sec / 10) << 4) | (sec % 10));

        data &= 0x7F; // Unhalt RTC
        write_ds1307(SEC_ADDR, data);

        CLEAR_DISP_SCREEN;
        clcd_print("TIME SET", LINE1(0));
        clcd_print("SUCCESS", LINE2(0));
        for (unsigned long wait = 500000; wait--;);
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
    } else if (key == MK_SW11) {
        CLEAR_DISP_SCREEN;
        state = e_dashboard;
    }

    time[0] = (hour / 10) + '0';
    time[1] = (hour % 10) + '0';
    time[3] = (min / 10) + '0';
    time[4] = (min % 10) + '0';
    time[6] = (sec / 10) + '0';
    time[7] = (sec % 10) + '0';

    switch (f_flag) {
        case 0:
            if (delay++ == 100) {
                clcd_print(time, LINE2(3));
            } else if (delay == 200) {
                delay = 0;
                clcd_print("  ", LINE2(3));
            }
            break;
        case 1:
            if (delay++ == 100) {
                clcd_print(time, LINE2(3));
            } else if (delay == 200) {
                delay = 0;
                clcd_print("  ", LINE2(6));
            }
            break;
        case 2:
            if (delay++ == 100) {
                clcd_print(time, LINE2(3));
            } else if (delay == 200) {
                delay = 0;
                clcd_print("  ", LINE2(9));
            }
            break;
    }
}
