#include "RSocket.h"

#define SERV_PORT 50000		/* bigger than 49152 */
#define LISTENQ 1024
#define RBUFF_SIZE 512

void str_cli(RS_SockFD sfd)
{
    char wbuff[RBUFF_SIZE], rbuff[RBUFF_SIZE];
    size_t n;
    
    memset((void*)wbuff, 0, sizeof(wbuff));
    memset((void*)rbuff, 0, sizeof(rbuff));
    
    while(1)
    {
	char * pchar = wbuff;
	int c;

	for(;;) {
	    c = fgetc(stdin);
	    if(c == EOF)
		return;
	    *pchar = c;
	    pchar ++;
	    if(c == '\n' || c == '\r')
	    {
		break;
	    }
	}
	*pchar = '\0';
	/* printf ("str[%d]:%s\n",strlen(wbuff),wbuff); */
	
	RS_write(sfd, wbuff, strlen(wbuff) + 1);
	RS_read(sfd, rbuff, strlen(wbuff) + 1);
	printf ("echo:%s\n",rbuff);
    }
}

int main(int argc, char *argv[])
{
    RS_SockFD sfd;
    struct sockaddr_in serv_addr;

    if (argc != 2)
    {
	printf ("usage client <server IP address>\n");
	exit(1);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    
    sfd = RS_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    RS_connect(sfd, (RS_SockAddr *) &serv_addr, sizeof(serv_addr));
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);
    
    str_cli(sfd);

    RS_close(sfd);
    
    return 0;
}
