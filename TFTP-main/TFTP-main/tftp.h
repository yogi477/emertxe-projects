/* Common file for server & client*/

#ifndef TFTP_H
#define TFTP_H

#include <stdint.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PORT 6969
#define BUFFER_SIZE 516  // TFTP data packet size (512 bytes data + 4 bytes header)
#define TIMEOUT_SEC 5    // Timeout in seconds
#define IP_ADDRESS  "127.0.0.1"
// TFTP OpCodes
typedef enum {
    RRQ = 1,  // Read Request
    WRQ = 2,  // Write Request
    DATA = 3, // Data Packet
    ACK = 4,  // Acknowledgment
    ERROR = 5 // Error Packet
} tftp_opcode;

// TFTP Packet Structure
#pragma pack(1)
typedef struct {
    uint16_t opcode; // Operation code (RRQ/WRQ/DATA/ACK/ERROR)
    union {
        struct {
            char filename[256];
            char mode[8];  // Typically "octet"
        } request;  // RRQ and WRQ
        struct {
            uint16_t block_number;
            char data[512];
        } data_packet; // DATA
        struct {
            uint16_t block_number;
        } ack_packet; // ACK
        struct {
            uint16_t error_code;
            char error_msg[512];
        } error_packet; // ERROR
    } body;
} tftp_packet;

void send_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename);
void receive_file(int sockfd, struct sockaddr_in client_addr, socklen_t client_len, char *filename);

int Connect();
void get(int sockfd,struct sockaddr *serv_addr,socklen_t *server_len,tftp_packet packet);
void put(int sockfd,struct sockaddr *cinfo,socklen_t *clilen,tftp_packet packet);


#endif

