#include "tftp.h"
#include "tftp_client.h"

extern int connect_count;
int main()
{
   int choice;
   char ch = 'y';
   tftp_client_t client;
   while(ch == 'y' || ch == 'Y')
   {
         printf("1.Connect\n2.Get\n3.Put\n4.Mode\n5.exit\nEnter the choice\n");
         scanf(" %d",&choice);

         switch(choice)
         {
            case 1:  {
                        printf("Enter the SERVER IP address");
                        getchar();
                        fgets(client.server_ip,sizeof(client.server_ip),stdin);
                        client.server_ip[strcspn(client.server_ip, "\n")] = '\0';
                        connect_to_server(&client,client.server_ip,9091);
                        break;
                     }

            case 2: if(connect_count != 0)
                    {
                        get(&client,NULL);
                        break;
                    }
                    else{
                     printf("First connect client to server\n");
                     exit(0);
                    }

            case 3: if(connect_count != 0)
                     {
                        put_file(&client);
                        break;
                     }
                      else
                     {
                     printf("First connect client to server\n");
                     exit(0);
                    }

            case 4: if(connect_count != 0)
                     {
                        mode(&client);
                        break;
                     }
                     else
                     {
                     printf("First connect client to server\n");
                     exit(0);
                  }

            case 5: exit(0);
         }
        printf("Do you wnat to continue(y/Y) in client opertion?\n");
        scanf(" %c",&ch);
    }

}
