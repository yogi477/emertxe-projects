void Left_scrolling(unsigned char str[])
{
       char temp =  str[0];
        for(int i = 0;i <= 15;i++)
        {
            str[i] = str[i+1];
        }
        str[15] = temp;
    
}