# This is a makefile for the DigitalRuin project.
# All rights reservied by Ruisen Luo
#

# Common variable settings
SHELL = /bin/sh

CC = gcc
AR = ar
ARFLAGS = -rcs
CFLAGS = -g
CPPFLAGS = -lstdc++
RELEASE = -O2

BIN_DIR = ./bin/
LIB_DIR = ./lib/
INCLUDE_DIR = ./include/
RESOURCE_DIR = ./resource/

ALL_OBJS =

## Recipe Templates
# Recipe for building C or C++ programs
# $1 target program name
# $2 c or cpp
define PROGRAM
$(1) : $$($(1)_src:%.$(2)=%.o)
ifeq ($(2),cpp)
	$(CC) $(CFLAGS) $$^ -o $(BIN_DIR)$$@ -L$(LIB_DIR) $$($(1)_lib:%=-l%) $(CPPFLAGS)
else
	$(CC) $(CFLAGS) $$^ -o $(BIN_DIR)$$@ -L$(LIB_DIR) $$($(1)_lib:%=-l%)
endif
$$($(1)_src:%.$(2)=%.o) : $$($(1)_src)
	$(CC) $(CFLAGS) -c $$^ -o $$@ -I$(INCLUDE_DIR) 
ALL_OBJS += $$($(1)_src:%.$(2)=%.o)
endef

# Recipe for building C or C++ static library
# $1 target lib name
# $2 c or cpp
define SLIB
$($(1):%=lib%.a) : $$($(1)_src:%.$(2)=%.o)
	$(AR) $(ARFLAGS) $(LIB_DIR)$$@ $$^

$$($(1)_src:%.$(2)=%.o) : $$($(1)_src)
	$(CC) $(CFLAGS) -c $$^ -o $$@ -I$(INCLUDE_DIR) 
ALL_OBJS += $$($(1)_src:%.$(2)=%.o)
endef

# Recipe for building C or C++ dynamic library
# $1 target lib name
define DLIB	
$($(1):%=lib%.so) : $$($(1)_src)
	$(CC) -shared $(CFLAGS) $$^ -o $(LIB_DIR)$$@ -I$(INCLUDE_DIR)
endef

# Project source file settings
programs = server controller client #Program list
slibs =				    #Static lib list
dlibs =				    #Dynamic lib list

all_target = $(programs) $(slibs:%=lib%.a) $(dlibs:%=lib%.so)

server_src = ./src/server/server.c
server_lib = 
controller_src = ./src/server/controller.c
controller_lib = 
client_src = ./src/client/client.c
client_lib = 

# Rules
.PHONY: clean all

all: $(all_target)

$(eval $(call PROGRAM,server,c))
$(eval $(call PROGRAM,controller,c))
$(eval $(call PROGRAM,client,c))

clean:
	-rm $(programs:%=$(BIN_DIR)%)
	-rm $(slibs:%=$(LIB_DIR)lib%.a)
	-rm $(dlibs:%=$(LIB_DIR)lib%.so)
	-rm $(ALL_OBJS)

