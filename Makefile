CC = gcc
CFLAGS = -g
#CPPFLAGS = 

server_src = ./src/server/server.c 
controller_src = ./src/server/controller.c
client_src = ./src/client/client.c

sources = $(server_src) $(controller_src) $(client_src)

.PHONY: clean all

all: server controller client

server : $(server_src:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

controller : $(controller_src:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

client : $(client_src:.c=.o)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	-rm server controller client
	-rm $(sources:.c=.d) $(sources:.c=.o) $(sources:.c=.d.*)

-include $(sources:.c=.d)

%.d: %.c
	set -e; rm -f $@; \
	$(CC) -M $(CFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
