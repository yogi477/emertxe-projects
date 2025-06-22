#include "tftp.h"
#include "tftp_client.h"
extern int connect_count;

void mode(tftp_client_t *client)  
{
    int choice;
    char ch = 'y';
    char *mode = NULL; // Mode string to pass to `get()`

    while (ch == 'y' || ch == 'Y')
    {
        printf("1. Normal_mode\n2. Octet_mode\n3. Netascii_mode\nEnter the choice: ");
        scanf(" %d", &choice);

        switch (choice)
        {
            case 1:  
                mode = "netascii";  // Normal mode treated as Netascii
                break;

            case 2:  
                mode = "octet";
                break;

            case 3:  
                mode = "netascii";
                break;

            default:
                printf("Invalid choice\n");
                continue;  
        }

        if (connect_count != 0)
        {
            get(client, mode);   
        }
        else
        {
            printf("First connect client to server\n");
            exit(0);
        }

        printf("Do you want to continue (y/Y) in mode operation? ");
        scanf(" %c", &ch);
    }
}
