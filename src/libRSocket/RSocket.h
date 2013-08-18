#ifndef _RSOCKET_H_
#define _RSOCKET_H_

#include <sys/socket.h>

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

#endif /* _RSOCKET_H_ */
