# Project source file settings

programs =  controller client server 	#Program list
slibs =	RSocket			   	#Static lib list
dlibs =				    	#Dynamic lib list

# The server program
server_ctype = c
server_src = ./src/server/server.c 
server_lib = RSocket
server_exlib =

# The controller program
controller_ctype = c
controller_src = ./src/server/controller.c
controller_lib =
controller_explib = 

# The client program
client_ctype = c
client_src = ./src/client/client.c
client_lib = RSocket
client_exlib = 

# the RSocket lib
RSocket_ctype = c
RSocket_src = ./src/libRSocket/RSocket.c
RSocket_lib =
RSocket_exlib =
RSocket_header = ./src/libRSocket/RSocket.h
