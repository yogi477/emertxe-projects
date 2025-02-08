void right_scrolling(unsigned char str[])
{
       char temp =  str[15];
        for(int i = 15;i >= 0;i--)
        {
            str[i] = str[i-1];
        }
        str[0] = temp;
    
}