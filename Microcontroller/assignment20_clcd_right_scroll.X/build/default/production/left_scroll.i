# 1 "left_scroll.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "left_scroll.c" 2
void Left_scrolling(unsigned char str[])
{
       char temp = str[0];
        for(int i = 0;i <= 15;i++)
        {
            str[i] = str[i+1];
        }
        str[15] = temp;

}
