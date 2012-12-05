#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 8888

int main(int argc, char *argv[ ])
{
  int sockfd;

  /* will hold the destination addr */
  struct sockaddr_in dest_addr;
  
  printf("I'm a client!\n");

  /* get a socket file descriptor */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Client-socket() error lol!");
    exit(1);
  }
  else
  {
    printf("Client-socket() sockfd is OK...\n");
  }

  /* host byte order */
  dest_addr.sin_family = AF_INET;

  /* short, network byte order */
  dest_addr.sin_port = htons(DEST_PORT);
  dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);

  /* zero the rest of the struct */
  memset(&(dest_addr.sin_zero), 0, 8);

  /* connect to server */
  if(connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("Client-connect() error lol");
    exit(1);
  }
  else
  {
    printf("Client-connect() is OK...\n");
  } 

  /*...other codes...*/

  return 0;
}
