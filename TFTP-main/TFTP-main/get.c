#include "tftp.h"

void get(int sockfd,struct sockaddr *cinfo,socklen_t *clilen,tftp_packet packet)
{
    // Display received data
    printf("Received filename: %s\n", packet.body.request.filename);
    printf("Received operation code: %d\n", packet.opcode);

    //file exitst 
    int fd = open(packet.body.request.filename,O_RDONLY);

    tftp_packet ack_packet;
    memset(&ack_packet,0,sizeof(ack_packet));
    ack_packet.opcode = ACK;
    if(fd == -1)
    {
      // File not found: Send ACK with failure status
      printf("File not found. Sending failure ACK.\n");
      ack_packet.body.ack_packet.block_number = 0;  // 0 = Failure
    } 
    else
    {
      // File found: Send ACK with success status
      printf("File found. Sending success ACK.\n");
      ack_packet.body.ack_packet.block_number = 1;  // 1 = Success
  }

  // Send ACK to client
  int ret_value = sendto(sockfd, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr*)cinfo, *clilen);
if(ret_value == -1)
{
    perror("sendto");
}
  //receive ack(2) from the client
  recvfrom(sockfd,&ack_packet,sizeof(ack_packet),0,(struct sockaddr*)cinfo,clilen);
  if (ack_packet.body.ack_packet.block_number != 2)
    {
        printf("ACK(2) not received. Aborting file transfer.\n");
        close(fd);
        return;
    }

    printf("ACK(2) received. Starting file transfer...\n");

    // Start sending file data
    tftp_packet data_packet;
    memset(&data_packet, 0, sizeof(data_packet));

    int block_num = 1;
    int bytes_read;

    while ((bytes_read = read(fd, data_packet.body.data_packet.data, 512)) > 0)
    {
        data_packet.opcode = htons(DATA);
        data_packet.body.data_packet.block_number = htons(block_num);

        sendto(sockfd, &data_packet, bytes_read + 4, 0, 
               (struct sockaddr*)cinfo, *clilen);

        printf("Sent block %d with %d bytes\n", block_num, bytes_read);

         // Receive ACK for the sent block
         recvfrom(sockfd, &ack_packet, sizeof(ack_packet), 0, (struct sockaddr*)cinfo, clilen);
         if (ntohs(ack_packet.body.ack_packet.block_number) != block_num)
         {
             printf("Unexpected ACK block number. Resending block %d...\n", block_num);
             continue;
         }
 
        block_num++;
    }
    printf("Transferred successfull\n");
    close(fd);
}