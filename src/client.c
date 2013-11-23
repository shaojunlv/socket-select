/**************************************************************************/
/* Generic client example is used with connection-oriented server designs */
/**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT  12345

main (int argc, char *argv[])
{
   int    len, rc;
   int    sockfd;
   char   send_buf[80];
   char   recv_buf[80];
   struct sockaddr_in   addr;

   /*************************************************/
   /* Create an AF_INET stream socket               */
   /*************************************************/
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   if (sockfd < 0)
   {
      perror("socket");
      exit(-1);
   }

   /*************************************************/
   /* Initialize the socket address structure       */
   /*************************************************/
   memset(&addr, 0, sizeof(addr));
   addr.sin_family      = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port        = htons(SERVER_PORT);

   /*************************************************/
   /* Connect to the server                         */
   /*************************************************/
   rc = connect(sockfd,
                (struct sockaddr *)&addr,
                sizeof(struct sockaddr_in));
   if (rc < 0)
   {
      perror("connect");
      close(sockfd);
      exit(-1);
   }
   printf("Connect completed.socketfd is %d .rc is %d \n",sockfd,rc);

   /*************************************************/
   /* Enter data buffer that is to be sent          */
   /*************************************************/
   printf("Enter message to be sent:\n");
   gets(send_buf);

   /*************************************************/
   /* Send data buffer to the worker job            */
   /*************************************************/
   len = send(sockfd, send_buf, strlen(send_buf) + 1, 0);
   if (len != strlen(send_buf) + 1)
   {
      perror("send");
      close(sockfd);
      exit(-1);
   }
   printf("%d bytes sent\n", len);

   /*************************************************/
   /* Receive data buffer from the worker job       */
   /*************************************************/
   len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
   if (len != strlen(send_buf) + 1)
   {
      perror("recv");
      close(sockfd);
      exit(-1);
   }
   printf("%d bytes received\n", len);

   /*************************************************/
   /* Close down the socket                         */
   /*************************************************/
   close(sockfd);
}
