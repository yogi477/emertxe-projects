#ifndef TFTP_CLIENT_H
#define TFTP_CLIENT_H

#include "tftp.h"
#pragma(1)
typedef struct {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t server_len;
    char server_ip[INET_ADDRSTRLEN];
} tftp_client_t;

// Function prototypes
void connect_to_server(tftp_client_t *client, char *ip, int port);
void put_file(tftp_client_t *client);
void get(tftp_client_t *client,char *mode);
void mode(tftp_client_t *client);

#endif