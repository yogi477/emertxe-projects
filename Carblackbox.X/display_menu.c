#include"black_box.h"
unsigned short flag = 0;
void display_main_menu(void)
{  
    if(flag == 0)
    {
        clcd_print("*",LINE1(0)); 
    }
    else
    {
        clcd_print("*",LINE2(0));
    }
    clcd_print(disp_menu[disp_index],LINE1(3));
     clcd_print(disp_menu[disp_index+1],LINE2(3));
     if(key == MK_SW1)
     {
         CLEAR_DISP_SCREEN; 
         if(flag == 0)
             flag = 0;
         else if(disp_index >= 0 && disp_index < 2)
         {
             disp_index++; 
         }
         flag = 1;
         if(menu_cnt >=0 && menu_cnt < 3)
            menu_cnt++;
         else if(menu_cnt == 3)
             menu_cnt = 3;
     }
     else if(key == MK_SW2)
     {
         CLEAR_DISP_SCREEN;
         if(flag == 1)
             flag = 1;
         else if(disp_index > 0 && disp_index <= 3)
         {
             flag = 1;
             disp_index--; 
         }
         flag = 0;
         if(menu_cnt > 0 && menu_cnt <= 3)
            menu_cnt--;
         else if(menu_cnt == 0)
             menu_cnt = 0;
            
     }
     else if(key == MK_SW11 && menu_cnt == 0)
     {
         CLEAR_DISP_SCREEN; 
         state = e_view_log;
     }
     else if(key == MK_SW11 && menu_cnt == 1)
     {
         CLEAR_DISP_SCREEN;
         state = e_clear_log;
     }
     else if(key == MK_SW11 && menu_cnt == 2)
     {
         CLEAR_DISP_SCREEN;
         state = e_download_log;
     }
     else if(key == MK_SW11 && menu_cnt == 3)
     {
         CLEAR_DISP_SCREEN;
         state = e_set_time;
     }
     else if(key == MK_SW12)
     {
         CLEAR_DISP_SCREEN; 
         state = e_dashboard;
     }
    
}