#include "tftp.h"

int main()
{
    if(Connect() == -1)
    {
        printf("Connection failed\n");
        return 0;
    }
}