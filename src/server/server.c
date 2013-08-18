#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* the port users will be connecting to */
#define MYPORT 8888
/* how many pending connections queue will hold */
#define BACKLOG 10

int main()
{
    /* listen on sock_fd, new connection on new_fd */
    int sockfd, new_fd;
    /* my address information, address where I run this program */
    struct sockaddr_in my_addr;
    /* remote address information */
    struct sockaddr_in their_addr;
    int sin_size;

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
    
    /* listen */
    if(listen(sockfd, BACKLOG) == -1)
    {
	perror("listen() error lol!");
	exit(1);
    }
    else
    {
	printf("listen() is Ok...\n");
    }

    /* ...other codes to read the received data... */
    sin_size = sizeof(struct sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    if(new_fd == -1)
    {
	perror("accept() error lol!");
    }
    else
    {
	printf("accept() is OK...\n");
    }
	    
    /* ...other codes... */

    /* close file descriptors */
    close(new_fd);
    close(sockfd);

    return 0;
}
