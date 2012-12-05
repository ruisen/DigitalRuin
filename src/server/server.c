#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 8888

void main()
{
  int sockfd;			/* socket file descriptor */
  struct sockaddr_in my_addr;

  printf("I'm a server...\n");
  
  /* get a socket file descriptor */
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Server-socket() error lol!");
    exit(1);
  }
  else
  {
    printf("Server-socket() sockfd is OK...\n");
  }

  /* host byte order */
  my_addr.sin_family = AF_INET;
  /* short nerwork byte order */
  my_addr.sin_port = htons(MYPORT);
  my_addr.sin_addr.s_addr = INADDR_ANY;
  /* zero the rest of the struct */
  memset(&(my_addr.sin_zero), 0, 8);

  /* bind a port */
  if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
  {
    perror("Server-bind() error lol!");
    exit(1);
  }
  else
  {
    printf("Server-bind() sockfd is OK...\n");
  }

  /* ...other codes... */

  return 0;
}
