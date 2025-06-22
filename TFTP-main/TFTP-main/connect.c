#include "tftp.h"

#define SERVER_BUFF 50
#define SERVER_PORT 9091
#define SERVER_IP "127.0.0.1"

int Connect()
{
    int sock_fd;
    struct sockaddr_in serv_addr, cli_addr;
    char serv_buffer[SERVER_BUFF];
    char server_ipaddr[50];

    // Create UDP socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) 
    {
        perror("Socket creation failed");
        return -1;
    }

    // Bind socket
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERVER_PORT);

    if (bind(sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) 
    {
        perror("Bind failed");
        close(sock_fd);
        return -1;
    }

    printf("Server is listening on port %d...\n", SERVER_PORT);
    socklen_t cli_len = sizeof(cli_addr);
    tftp_packet packet;

    while (1)
    {
        int bytes_received = recvfrom(sock_fd, &packet, sizeof(packet), 0,
                              (struct sockaddr*)&cli_addr, &cli_len);

                if (bytes_received < 0)
                {
                    perror("recvfrom() failed");
                    continue; // Continue the loop if `recvfrom()` fails
                }

                printf("Bytes received: %d\n", bytes_received);
                printf("Received opcode (ntohs): %d\n", packet.opcode);

        if (packet.opcode == RRQ)
        {
            get(sock_fd, (struct sockaddr*)&cli_addr, &cli_len,packet);
        }
        else if (packet.opcode == WRQ)
        {
            put(sock_fd, (struct sockaddr*)&cli_addr, &cli_len,packet);
        }
        else
        {
            printf("Unknown opcode received: %d\n", packet.opcode);
        }
    }

    close(sock_fd);
    return 1;
}
