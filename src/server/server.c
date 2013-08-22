#include "RSocket.h"

#define SERV_PORT 50000		/* bigger than 49152 */
#define LISTENQ 1024
#define RBUFF_SIZE 512

void str_echo(RS_SockFD sfd, struct sockaddr_in * pcliaddr)
{
    size_t n;
    char buf[RBUFF_SIZE];
    char str_addr[INET_ADDRSTRLEN];
    char str_cliaddr[INET_ADDRSTRLEN];

    struct sockaddr_storage ss;
    socklen_t len;
    struct sockaddr_in *psin;

    psin = &ss;

    len = sizeof(ss);
    getsockname(sfd, (RS_SockFD *) &ss, &len);

    inet_ntop(AF_INET, &psin->sin_addr, str_addr, sizeof(str_addr));
    inet_ntop(AF_INET, &pcliaddr->sin_addr, str_cliaddr, sizeof(str_cliaddr));

    while(1)
    {
	/* n = RS_read(sfd, buf,sizeof(buf)); */
	n = read(sfd, buf,sizeof(buf));
	if(n > 0)
	{
	    printf ("recieve[%d chars; server %s:%d; client %s:%d]:%s\n", n, str_addr, ntohs(psin->sin_port), str_cliaddr, ntohs(pcliaddr->sin_port), buf);
	    RS_write(sfd,buf,n); 
	}
	else if (n == 0)
	{
	    return;
	}
    }
}

int main()
{
    RS_SockFD sfdlisten, sfdconnect;
    pid_t childpid;
    RS_SockLen childsock_len;
    struct sockaddr_in serv_addr, child_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    sfdlisten = RS_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    RS_bind(sfdlisten, (RS_SockAddr *) &serv_addr, sizeof(serv_addr));
    RS_listen(sfdlisten, LISTENQ);
    
    while(1)
    {
	childsock_len = sizeof(child_addr);
	sfdconnect = RS_accept(sfdlisten, (RS_SockAddr *)&child_addr, &childsock_len);
	
	if ((childpid = fork()) == 0)
	{
	    RS_close(sfdlisten);
	    str_echo(sfdconnect, &child_addr);
	    RS_close(sfdconnect);
	    printf ("One child process closed\n");
	    break;
	}
	else
	{
	    RS_close(sfdconnect);
	}
    }
    
    
    return 0;
}
