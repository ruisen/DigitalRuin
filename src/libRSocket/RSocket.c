/****************************************************************
 * File Name: RSocket.c
 * Create Time: Sun Aug 25 12:31:46 2013
 * Author: Ruisen Luo
 * Description: 
 ****************************************************************/

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

RS_SockFD RS_accept(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen *pslen)
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

ssize_t RS_read(RS_SockFD sfd, void *pbuff, size_t n)
{
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = pbuff;
    nleft = n;

    while(nleft > 0)
    {
	if ((nread = read(sfd, pbuff, nleft)) < 0)
	{
	    if (errno == EINTR)
	    {
		nread = 0;	/* If got interrupted, call read again */
	    }
	    else if(errno == EAGAIN || errno == EWOULDBLOCK) 
	    {
		break;		/* O_NONBLOCK socket, and no data is waiting to be received */
	    }
	    else
	    {
		_error("read error"); /* Got something wrong */
	    }
	}
	else if (nread == 0)
	{
	    break;		/* EOF */
	}

	nleft -= nread;
	ptr += nread;
    }

    nread = n - nleft;	/* Use nread again to represent total read count */

    if (nread < 0)
    {
	_error("read error");	/* This must be an error! */
    }

    return nread;
}

void RS_write(RS_SockFD sfd, const void *pbuff, size_t n)
{
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = pbuff;
    nleft = n;

    while(nleft > 0)
    {
	if ((nwritten = write(sfd, pbuff, nleft)) <= 0)
	{
	    if (nwritten < 0 && errno == EINTR)
	    {
		nwritten = 0;
	    }
	    else
	    {
		_error("write error");
	    }
	}

	nleft -= nwritten;
	ptr += nwritten;
    }
    
}
