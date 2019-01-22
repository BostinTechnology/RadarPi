## -*- Makefile -*-
##
## User: matthew
## Time: 12-Jan-2019 09:16:44
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g -Wall
CFLAGS = $(BASICOPTS)


# Define the target directories.
TARGETDIR_testProgram=build


all: $(TARGETDIR_testProgram)/testProgram

## Target: testProgram
OBJS_testProgram =  \
	$(TARGETDIR_testProgram)/ledTest.o \
	$(TARGETDIR_testProgram)/adcTest.o \
	$(TARGETDIR_testProgram)/gainTest.o \
	$(TARGETDIR_testProgram)/freqTest.o \
	$(TARGETDIR_testProgram)/adcFunctions.o \
	$(TARGETDIR_testProgram)/gainFunctions.o \
	$(TARGETDIR_testProgram)/gpioFunctions.o \
	$(TARGETDIR_testProgram)/spi_comms.o \
	$(TARGETDIR_testProgram)/gpio_control.o \
	$(TARGETDIR_testProgram)/utilities.o \
	$(TARGETDIR_testProgram)/ledControl.o \
	$(TARGETDIR_testProgram)/mainTestProgram.o
USERLIBS_testProgram = -lbcm2835 
DEPLIBS_testProgram =  
LDLIBS_testProgram = $(USERLIBS_testProgram)


# Link or archive
$(TARGETDIR_testProgram)/testProgram: $(TARGETDIR_testProgram) $(OBJS_testProgram) $(DEPLIBS_testProgram)
	$(LINK.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ $(OBJS_testProgram) $(LDLIBS_testProgram)


# Compile source files into .o files
$(TARGETDIR_testProgram)/ledTest.o: $(TARGETDIR_testProgram) TestProgram/src/ledTest.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/ledTest.c

$(TARGETDIR_testProgram)/adcTest.o: $(TARGETDIR_testProgram) TestProgram/src/adcTest.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/adcTest.c

$(TARGETDIR_testProgram)/freqTest.o: $(TARGETDIR_testProgram) TestProgram/src/freqTest.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/freqTest.c

$(TARGETDIR_testProgram)/gainFunctions.o: $(TARGETDIR_testProgram) common/src/gainFunctions.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/gainFunctions.c

$(TARGETDIR_testProgram)/gainTest.o: $(TARGETDIR_testProgram) TestProgram/src/gainTest.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/gainTest.c

$(TARGETDIR_testProgram)/mainTestProgram.o: $(TARGETDIR_testProgram) TestProgram/src/mainTestProgram.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ TestProgram/src/mainTestProgram.c

$(TARGETDIR_testProgram)/adcFunctions.o: $(TARGETDIR_testProgram) common/src/adcFunctions.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/adcFunctions.c

$(TARGETDIR_testProgram)/gpioFunctions.o: $(TARGETDIR_testProgram) common/src/gpioFunctions.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/gpioFunctions.c

$(TARGETDIR_testProgram)/spi_comms.o: $(TARGETDIR_testProgram) common/src/spi_comms.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/spi_comms.c

$(TARGETDIR_testProgram)/gpio_control.o: $(TARGETDIR_testProgram) common/src/gpio_control.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/gpio_control.c

$(TARGETDIR_testProgram)/utilities.o: $(TARGETDIR_testProgram) common/src/utilities.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/utilities.c

$(TARGETDIR_testProgram)/ledControl.o: $(TARGETDIR_testProgram) common/src/ledControl.c
	$(COMPILE.c) $(CFLAGS_testProgram) $(CPPFLAGS_testProgram) -o $@ common/src/ledControl.c



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_testProgram)/testProgram \
		$(TARGETDIR_testProgram)/ledTest.o \
		$(TARGETDIR_testProgram)/adcTest.o \
		$(TARGETDIR_testProgram)/freqTest.o \
		$(TARGETDIR_testProgram)/gainTest.o \
		$(TARGETDIR_testProgram)/mainTestProgram.o \
		$(TARGETDIR_testProgram)/adcFunctions.o \
		$(TARGETDIR_testProgram)/gpioFunctions.o \
		$(TARGETDIR_testProgram)/spi_comms.o \
		$(TARGETDIR_testProgram)/gpio_control.o \
		$(TARGETDIR_testProgram)/utilities.o \
		$(TARGETDIR_testProgram)/ledControl.o
	rm -f -r $(TARGETDIR_testProgram)


# Create the target directory (if needed)
$(TARGETDIR_testProgram):
	mkdir -p $(TARGETDIR_testProgram)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux

