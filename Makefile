## -*- Makefile -*-
##
## User: matthew
## Time: 31-Dec-2018 10:34:45
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_testProgram=.


all: testProgram

## Target: testProgram
OBJS_testProgram =  \
	$(TARGETDIR_testProgram)/gpio_control.o \
	$(TARGETDIR_testProgram)/utilities.o \
	$(TARGETDIR_testProgram)/mainTestProgram.o \
	$(TARGETDIR_testProgram)/ledControl.o
USERLIBS_testProgram = $(SYSLIBS_testProgram) TestProgram/inc/utilities.h TestProgram/inc/systemSettings.h TestProgram/inc/ledControl.h TestProgram/inc/gpio_control.h 
DEPLIBS_testProgram =     
LDLIBS_testProgram = $(USERLIBS_testProgram)


# Link or archive
$(TARGETDIR_testProgram)/testProgram: $(TARGETDIR_testProgram) $(OBJS_testProgram) $(DEPLIBS_testProgram)
	$(LINK.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ $(OBJS_testProgram) $(LDLIBS_testProgram)


# Compile source files into .o files
$(TARGETDIR_testProgram)/ledControl.o: $(TARGETDIR_testProgram) TestProgram/src/ledControl.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/ledControl.c

$(TARGETDIR_testProgram)/gpio_control.o: $(TARGETDIR_testProgram) TestProgram/src/gpio_control.c
	$(COMPILE.c) $(CFLAGS_testProgram) -o $@ TestProgram/src/gpio_control.c

$(TARGETDIR_testProgram)/utilities.o: $(TARGETDIR_testProgram) TestProgram/src/utilities.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/utilities.c

$(TARGETDIR_testProgram)/mainTestProgram.o: $(TARGETDIR_testProgram) TestProgram/src/mainTestProgram.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/mainTestProgram.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_testProgram)/testProgram \
		$(TARGETDIR_testProgram)/gpio_control.o \
		$(TARGETDIR_testProgram)/utilities.o \
		$(TARGETDIR_testProgram)/mainTestProgram.o \
		$(TARGETDIR_testProgram)/ledControl.o
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux
