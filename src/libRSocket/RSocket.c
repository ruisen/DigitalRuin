#include "RSocket.h"

RS_SockFD RS_socket(int family, int type, int protocol)
{
    RS_SockFD sfd;
    if ((sfd = socket(family,type,protocol)) < 0)
    {
	exit(1);		/* TODO : Add error log here */
    }

    return sfd;
}

void RS_connect(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen slen)
{
    if (connect(sfd, psa, slen) < 0)
    {
	exit(1);		/* TODO : Add error log here */
    }
}
