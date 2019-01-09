## -*- Makefile -*-
##
## User: matthew
## Time: 09-Jan-2019 21:04:50
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
CPPFLAGS_testProgram = \
	-Icommon/src/gpio_control.c \
	-Icommon/src/utilities.c \
	-Icommon/src/ledControl.c \
	-ITestProgram/src/ledTest.c \
	-ITestProgram/src/mainTestProgram.c
OBJS_testProgram =  \
	$(TARGETDIR_testProgram)/gpio_control.o \
	$(TARGETDIR_testProgram)/utilities.o \
	$(TARGETDIR_testProgram)/ledControl.o \
	$(TARGETDIR_testProgram)/ledTest.o \
	$(TARGETDIR_testProgram)/mainTestProgram.o
USERLIBS_testProgram = $(SYSLIBS_testProgram) 
DEPLIBS_testProgram =  
LDLIBS_testProgram = $(USERLIBS_testProgram)


# Link or archive
$(TARGETDIR_testProgram)/testProgram: $(TARGETDIR_testProgram) $(OBJS_testProgram) $(DEPLIBS_testProgram)
	$(LINK.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ $(OBJS_testProgram) $(LDLIBS_testProgram)


# Compile source files into .o files
$(TARGETDIR_testProgram)/gpio_control.o: $(TARGETDIR_testProgram) common/src/gpio_control.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/gpio_control.c

$(TARGETDIR_testProgram)/utilities.o: $(TARGETDIR_testProgram) common/src/utilities.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/utilities.c

$(TARGETDIR_testProgram)/ledControl.o: $(TARGETDIR_testProgram) common/src/ledControl.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/ledControl.c

$(TARGETDIR_testProgram)/ledTest.o: $(TARGETDIR_testProgram) TestProgram/src/ledTest.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/ledTest.c

$(TARGETDIR_testProgram)/mainTestProgram.o: $(TARGETDIR_testProgram) TestProgram/src/mainTestProgram.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/mainTestProgram.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_testProgram)/testProgram \
		$(TARGETDIR_testProgram)/gpio_control.o \
		$(TARGETDIR_testProgram)/utilities.o \
		$(TARGETDIR_testProgram)/ledControl.o \
		$(TARGETDIR_testProgram)/ledTest.o \
		$(TARGETDIR_testProgram)/mainTestProgram.o
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux

