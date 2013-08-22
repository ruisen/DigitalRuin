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
#This __[pname]_target target is used for adding lib requiement to that program
__$(1)_program : $$($(1)_lib:%=lib%.a) $(1) 
	@echo Successful build PROGRAM $(1)

$(1) : $$($(1)_src:%.$(2)=%.o)
ifeq ($(2),cpp)
	$(CC) $(CFLAGS) $$^ -o $(BIN_DIR)$$@ -L$(LIB_DIR) $$($(1)_lib:%=-l%) $$($(1)_exlib:%=-l%)  $(CPPFLAGS)
else
	$(CC) $(CFLAGS) $$^ -o $(BIN_DIR)$$@ -L$(LIB_DIR) $$($(1)_lib:%=-l%) $$($(1)_exlib:%=-l%)
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
	cp $($(1)_header) $(INCLUDE_DIR)
	@echo Successful build SLIB $(1)

$(foreach src,$($(1)_src),$(call OBJ,$(src),$(2)))

ALL_OBJS += $$($(1)_src:%.$(2)=%.o)

endef

# Recipe for building C or C++ dynamic library
# $1 target lib name
define DLIB	
lib$(1).so : $$($(1)_src)
	$(CC) -shared $(CFLAGS) $$^ -o $(LIB_DIR)$$@ -I$(INCLUDE_DIR)
	@echo Successful build DLIB $(1)

endef

##############################>>>
include project.mk
##############################<<<

all_target = $(programs:%=__%_program) $(slibs:%=lib%.a) $(dlibs:%=lib%.so)

# Rules
.PHONY: clean all

all: $(all_target)

$(foreach slib,$(slibs),$(eval $(call SLIB,$(slib),$($(slib)_ctype))))
$(foreach dlib,$(dlibs),$(eval $(call DLIB,$(dlib),$($(dlib)_ctype))))
$(foreach program,$(programs),$(eval $(call PROGRAM,$(program),$($(program)_ctype))))

clean:
	-rm -f $(programs:%=$(BIN_DIR)%) 2>/dev/null
	-rm -f $(slibs:%=$(LIB_DIR)lib%.a) 2>/dev/null
	-rm -f $(dlibs:%=$(LIB_DIR)lib%.so) 2>/dev/null
	-rm -f $(ALL_OBJS) 2>/dev/null
	@echo Clean up completed!

