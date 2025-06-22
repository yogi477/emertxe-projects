#include "tftp.h"

void put(int sockfd,struct sockaddr *cinfo,socklen_t *clilen,tftp_packet packet)
{
    //char buffer[512];

    // Receive WRQ packet (Write Request)
    // tftp_packet packet;
    // memset(&packet, 0, sizeof(packet));

    // int ret = recvfrom(sockfd, &packet, sizeof(packet), 0, 
    //                    (struct sockaddr*)cinfo, clilen);
    // if (ret == -1)
    // {
    //     perror("Error receiving WRQ packet");
    //     return;
    // }

    // Display received data
    printf("Received WRQ for file: %s\n", packet.body.request.filename);

    // Check if file exists - Create or Truncate
    int fd = open(packet.body.request.filename, O_TRUNC | O_WRONLY, 0644);
    if (fd == -1)  
    {
        fd = open(packet.body.request.filename, O_CREAT | O_WRONLY, 0644);
        if (fd == -1)
        {
            perror("Error opening file for writing");
            return;
        }
    }
    // Send ACK(0) to confirm readiness
    tftp_packet ack_packet;
    memset(&ack_packet, 0, sizeof(ack_packet));
    ack_packet.opcode = ACK;
    ack_packet.body.ack_packet.block_number = htons(0);  // ACK(0)

    sendto(sockfd, &ack_packet, sizeof(ack_packet), 0, 
           (struct sockaddr*)cinfo, *clilen);

    printf("ACK(0) sent. Ready to receive data.\n");

    //sending ack(2) to client file is present send the content in the file
    ack_packet.opcode = ACK;
    ack_packet.body.ack_packet.block_number = htons(2);
    sendto(sockfd,&ack_packet,sizeof(ack_packet),0,(struct sockaddr*)cinfo,*clilen);
    
    printf("File '%s' is ready to receive data.\n", packet.body.request.filename);

    // data packets recving from the client
    tftp_packet data_packet;
    int expected_block_num = 1;

    while (1)
    {
        memset(&data_packet, 0, sizeof(data_packet));

        int ret = recvfrom(sockfd, &data_packet, sizeof(data_packet), 0, 
                       (struct sockaddr*)cinfo, clilen);
        if (ret == -1)
        {
            perror("Error receiving data packet");
            close(fd);
            return;
        }

        if (ntohs(data_packet.opcode) != DATA)
        {
            printf("Invalid packet received, expected DATA.\n");
            close(fd);
            return;
        }

        int block_number = ntohs(data_packet.body.data_packet.block_number);

        if (block_number != expected_block_num)
        {
            printf("Unexpected block number %d (expected %d), ignoring.\n", 
                   block_number, expected_block_num);
            continue;
        }

        write(fd, data_packet.body.data_packet.data, ret - 4);
        printf("Received block %d, writing to file...\n", block_number);

        // Send ACK for the received block
        ack_packet.opcode = htons(ACK);
        ack_packet.body.ack_packet.block_number = htons(block_number);

        sendto(sockfd, &ack_packet, sizeof(ack_packet), 0, 
               (struct sockaddr*)cinfo, *clilen);

        // Check for end of transmission
        if (ret < 516) // 512 bytes of data + 4 bytes (header)
        {
            printf("Last block received, file transfer complete.\n");
            break;
        }

        expected_block_num++;
    }

   
    printf("File successfully saved on the server.\n");
    close(fd);
}

