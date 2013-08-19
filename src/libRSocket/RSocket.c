#include "RSocket.h"

/* a very simple error function */
void _error(const char *emsg)
{
    fprintf(stderr, "RSocket ERROR:%s\n", emsg);
    exit(1);
}


RS_SockFD RS_socket(int family, int type, int protocol)
{
    RS_SockFD sfd;
    if ((sfd = socket(family,type,protocol)) < 0)
    {
	_error("socket error");
    }

    return sfd;
}

void RS_connect(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen slen)
{
    if (connect(sfd, psa, slen) < 0)
    {
	_error("connect error");
    }
}

void RS_bind(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen slen)
{
    if (bind(sfd, psa, slen) < 0)
    {
	_error("bind error");
    }
}

void RS_listen(RS_SockFD sfd, int backlog)
{
    if (listen(sfd,backlog) < 0)
    {
	_error("listen error");
    }
}

RS_SockFD RS_Accept(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen *pslen)
{
    RS_SockFD fd;

    while ((fd = accept(sfd, psa, pslen)) < 0)
    {
	if(errno == ECONNABORTED)
	{
	    continue;
	}
	else
	{
	    _error("accept error");
	}
    }

    return fd;
}

void RS_close(RS_SockFD sfd)
{
    if (close(sfd) < 0)
    {
	_error("close error");
    }
}
