#ifndef _RSOCKET_H_
#define _RSOCKET_H_

/* POSIX headers */
#include <sys/socket.h>
#include <errno.h>
/* std C headers */
#include <stdlib.h>
#include <stdio.h>

/* +MACROS */
/* |-MACRO DEFINE */
#define RS_SockFD int			/* Socket file descriptor */
#define RS_SockAddr struct sockaddr	/* Generic socket address struct */
#define RS_SockLen socklen_t		/* Socket length */

/* |-MACRO FUNCTIONS */


/* +FUNCTION DECLARE */
/* |-RS_socket : This is a wrapper to the system call socket in sys/socket.h
   | Params:
   |     family : Protocol family
   |     type : Socket type
   |     protocol : protocol to use
   | Return:
   |     socket decriptor returned by the system call*/
RS_SockFD RS_socket(int family, int type, int protocol);

/* |-RS_connect : wrapper to socket coonect system call
   | Params:
   |     sfd : socket file descriptor
   |     psa : socket address to connect
   |     slen : socket address struct length*/
void RS_connect(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen slen);

/* |-RS_bind : wrapper to socket bind system call
   | Params:
   |     sfd : socket file descriptor
   |     psa : socket address and port to bind
   |     slen : socket address struct length*/
void RS_bind(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen slen);

/* |-RS_listen : wrapper to socket bind system listen
   | Params:
   |     sfd : socket file descriptor
   |     backlog : maximum size for the connction queues*/
void RS_listen(RS_SockFD sfd, int backlog);

/* |-RS_accept : wrapper to socket accept system call
   | Params:
   |     sfd : socket file descriptor
   |     psa : socket address of the currently connected peer process
   |     slen : socket address struct length
   | Return:
   |     the currently connected peer process' socket file descriptor*/
RS_SockFD RS_accept(RS_SockFD sfd, RS_SockAddr *psa, RS_SockLen *pslen);

/* |-RS_close : wrapper to socket close system call
   | Params:
   |     sfd : the socket file descriptor we decrease its reference count*/
void RS_close(RS_SockFD sfd);

/* |-RS_read : read at most n bytes from specified socket into a buffer
   | Params:
   |     sfd : socket file descriptor
   |     pbuff : read buffer
   |     n : numbers of bytes want to read
   | Return:
   |     the exactly number of bytes read*/
ssize_t RS_read(RS_SockFD sfd, void *pbuff, size_t n);

#endif /* _RSOCKET_H_ */
