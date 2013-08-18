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

# Recipe for building c or c++ obj files
# $1 source file
# $2 c or cpp
define OBJ

ifeq ($(2),cpp)
$(patsubst %.$(2),%.o,$(1)) : $(1)
	$(CC) $(CFLAGS) -c $$^ -o $$@ -I$(INCLUDE_DIR) $(CPPFLAGS)

else
$(patsubst %.$(2),%.o,$(1)) : $(1)
	$(CC) $(CFLAGS) -c $$^ -o $$@ -I$(INCLUDE_DIR)

endif

endef

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

$(foreach src,$($(1)_src),$(call OBJ,$(src),$(2)))

ALL_OBJS += $$($(1)_src:%.$(2)=%.o)

endef

# Recipe for building C or C++ static library
# $1 target lib name
# $2 c or cpp
define SLIB
lib$(1).a : $$($(1)_src:%.$(2)=%.o)
	$(AR) $(ARFLAGS) $(LIB_DIR)$$@ $$^

$(foreach src,$($(1)_src),$(call OBJ,$(src),$(2)))

ALL_OBJS += $$($(1)_src:%.$(2)=%.o)

endef

# Recipe for building C or C++ dynamic library
# $1 target lib name
define DLIB	
lib$(1).so : $$($(1)_src)
	$(CC) -shared $(CFLAGS) $$^ -o $(LIB_DIR)$$@ -I$(INCLUDE_DIR)

endef

##############################>>>
# Project source file settings
programs =  controller client #Program list
slibs =	server			    #Static lib list
dlibs =				    #Dynamic lib list

server_src = ./src/server/hi.cpp  #./src/server/server.c 
server_lib =
server_ctype = cpp
controller_src = ./src/server/controller.c
controller_lib = 
controller_ctype = c
client_src = ./src/client/client.c
client_lib = 
client_ctype = c
##############################<<<

all_target = $(programs) $(slibs:%=lib%.a) $(dlibs:%=lib%.so)

# Rules
.PHONY: clean all

all: $(all_target)

$(foreach slib,$(slibs),$(eval $(call SLIB,$(slib),$($(slib)_ctype))))
$(foreach dlib,$(dlibs),$(eval $(call DLIB,$(dlib),$($(dlib)_ctype))))
$(foreach program,$(programs),$(eval $(call PROGRAM,$(program),$($(program)_ctype))))

clean:
	-rm $(programs:%=$(BIN_DIR)%)
	-rm $(slibs:%=$(LIB_DIR)lib%.a)
	-rm $(dlibs:%=$(LIB_DIR)lib%.so)
	-rm $(ALL_OBJS)

