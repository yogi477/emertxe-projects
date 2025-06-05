# 1 "int_to_str.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Users/yogiy/.mchp_packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "int_to_str.c" 2
void int_to_str(int num, char *str) {
    int i = 0, rem;


    if (num < 0) {
        str[i++] = '-';
        num = -num;
    }


    int temp = num;
    while (temp > 0) {
        temp /= 10;
        i++;
    }

    str[i] = '\0';


    while (num > 0) {
        rem = num % 10;
        str[--i] = rem + '0';
        num /= 10;
    }
}
