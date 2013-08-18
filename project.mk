# Project source file settings

programs =  controller client server 	#Program list
slibs =	RSocket			   	#Static lib list
dlibs =				    	#Dynamic lib list

server_src = ./src/server/server.c 
server_lib = RSocket
server_ctype = c
controller_src = ./src/server/controller.c
controller_lib = 
controller_ctype = c
client_src = ./src/client/client.c
client_lib = 
client_ctype = c

RSocket_src = ./src/libRSocket/RSocket.c
RSocket_lib =
RSocket_ctype = c
