## -*- Makefile -*-
##
## User: Matthew
## Time: 12-Jan-2019 09:16:44
##
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
BASICOPTS = -g -Wall
CFLAGS = $(BASICOPTS)
PTHREAD=-pthread

# Define the target directories.
TARGETDIR_ALL=build


all:    $(TARGETDIR_ALL)/analogueMeasurement $(TARGETDIR_ALL)/testProgram $(TARGETDIR_ALL)/gainControl \
	$(TARGETDIR_ALL)/digitalDetection $(TARGETDIR_ALL)/sampleSoftware $(TARGETDIR_ALL)/radarVisual

# ----------------------------------------------------------------------------------------------------------------
#       Common Objects
# ----------------------------------------------------------------------------------------------------------------
OBJS_common = \
	$(TARGETDIR_ALL)/adcFunctions.o \
	$(TARGETDIR_ALL)/gainFunctions.o \
	$(TARGETDIR_ALL)/gpioFunctions.o \
	$(TARGETDIR_ALL)/spi_comms.o \
	$(TARGETDIR_ALL)/gpio_control.o \
	$(TARGETDIR_ALL)/ledControl.o \
	$(TARGETDIR_ALL)/utilities.o \

# ----------------------------------------------------------------------------------------------------------------
##      Target: testProgram
# ----------------------------------------------------------------------------------------------------------------
OBJS_testProgram =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/adcTest.o \
	$(TARGETDIR_ALL)/mainTestProgram.o
USERLIBS_testProgram = -lbcm2835 
DEPLIBS_testProgram =  
LDLIBS_testProgram = $(USERLIBS_testProgram)

# ----------------------------------------------------------------------------------------------------------------
##      Target: analogueMeasurement
# ----------------------------------------------------------------------------------------------------------------
OBJS_analogueMeasurement =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/readingAnalogueSignals.o
USERLIBS_analogueMeasurement = -lbcm2835 
DEPLIBS_analogueMeasurement =  
LDLIBS_analogueMeasurement = $(USERLIBS_analogueMeasurement)

# ----------------------------------------------------------------------------------------------------------------
##      Target: settingGainControl
# ----------------------------------------------------------------------------------------------------------------
OBJS_settingGainControl =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/settingGainControl.o
USERLIBS_settingGainControl = -lbcm2835 
DEPLIBS_settingGainControl =  
LDLIBS_settingGainControl = $(USERLIBS_settingGainControl)


# ----------------------------------------------------------------------------------------------------------------
##      Target: digitalDetection
# ----------------------------------------------------------------------------------------------------------------
OBJS_digitalDetection =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/readingDigitalSignals.o
USERLIBS_digitalDetection = -lbcm2835 
DEPLIBS_digitalDetection =  
LDLIBS_digitalDetection = $(USERLIBS_digitalDetection)

# ----------------------------------------------------------------------------------------------------------------
##      Target: sampleSoftware
# ----------------------------------------------------------------------------------------------------------------
OBJS_sampleSoftware =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/mainSampleSoftware.o
USERLIBS_sampleSoftware = -lbcm2835 
DEPLIBS_sampleSoftware =  
LDLIBS_sampleSoftware = $(USERLIBS_sampleSoftware)

# ----------------------------------------------------------------------------------------------------------------
##      Target: radarVisual
# ----------------------------------------------------------------------------------------------------------------
OBJS_radarVisual =  \
	$(OBJS_common) \
	$(TARGETDIR_ALL)/radarVisual.o
USERLIBS_radarVisual = -lbcm2835 -lm
GTKLIB =`pkg-config --cflags --libs gtk+-3.0`
DEPLIBS_radarVisual =  
LDLIBS_radarVisual = $(PTHREAD) $(USERLIBS_radarVisual) -export-dynamic
# ----------------------------------------------------------------------------------------------------------------
#       Link or archive
# ----------------------------------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/testProgram: $(TARGETDIR_ALL) $(OBJS_testProgram) $(DEPLIBS_testProgram)
	$(LINK.c) $(CFLAGS)  -o $@ $(OBJS_testProgram)  $(LDLIBS_testProgram)

$(TARGETDIR_ALL)/analogueMeasurement: $(TARGETDIR_ALL) $(OBJS_analogueMeasurement) $(DEPLIBS_analogueMeasurement)
	$(LINK.c) $(CFLAGS)  -o $@ $(OBJS_analogueMeasurement)  $(LDLIBS_analogueMeasurement)

$(TARGETDIR_ALL)/gainControl: $(TARGETDIR_ALL) $(OBJS_settingGainControl) $(DEPLIBS_settingGainControl)
	$(LINK.c) $(CFLAGS)  -o $@ $(OBJS_settingGainControl)  $(LDLIBS_settingGainControl)

$(TARGETDIR_ALL)/digitalDetection: $(TARGETDIR_ALL) $(OBJS_digitalDetection) $(DEPLIBS_digitalDetection)
	$(LINK.c) $(CFLAGS)  -o $@ $(OBJS_digitalDetection)  $(LDLIBS_digitalDetection)	

$(TARGETDIR_ALL)/sampleSoftware: $(TARGETDIR_ALL) $(OBJS_sampleSoftware) $(DEPLIBS_sampleSoftware)
	$(LINK.c) $(CFLAGS)  -o $@ $(OBJS_sampleSoftware)  $(LDLIBS_sampleSoftware)		

$(TARGETDIR_ALL)/radarVisual: $(TARGETDIR_ALL) $(OBJS_radarVisual) $(DEPLIBS_radarVisual)
	$(LINK.c) $(CFLAGS)  $(GTKLIB) -o $@ $(OBJS_radarVisual)  $(LDLIBS_radarVisual)
# ----------------------------------------------------------------------------------------------------------------
#       Compile source files into .o files
# ----------------------------------------------------------------------------------------------------------------
# ----- common ---------------------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/adcFunctions.o: $(TARGETDIR_ALL) common/src/adcFunctions.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/adcFunctions.c

$(TARGETDIR_ALL)/gainFunctions.o: $(TARGETDIR_ALL) common/src/gainFunctions.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/gainFunctions.c

$(TARGETDIR_ALL)/gpioFunctions.o: $(TARGETDIR_ALL) common/src/gpioFunctions.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/gpioFunctions.c

$(TARGETDIR_ALL)/gpio_control.o: $(TARGETDIR_ALL) common/src/gpio_control.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/gpio_control.c

$(TARGETDIR_ALL)/ledControl.o: $(TARGETDIR_ALL) common/src/ledControl.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/ledControl.c

$(TARGETDIR_ALL)/spi_comms.o: $(TARGETDIR_ALL) common/src/spi_comms.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/spi_comms.c

$(TARGETDIR_ALL)/utilities.o: $(TARGETDIR_ALL) common/src/utilities.c
	$(COMPILE.c) $(CFLAGS)  -o $@ common/src/utilities.c

# ----- testProgram ----------------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/adcTest.o: $(TARGETDIR_ALL) TestProgram/src/adcTest.c
	$(COMPILE.c) $(CFLAGS)  -o $@ TestProgram/src/adcTest.c

$(TARGETDIR_ALL)/ledTest.o: $(TARGETDIR_ALL) TestProgram/src/ledTest.c
	$(COMPILE.c) $(CFLAGS)  -o $@ TestProgram/src/ledTest.c

$(TARGETDIR_ALL)/mainTestProgram.o: $(TARGETDIR_ALL) TestProgram/src/mainTestProgram.c
	$(COMPILE.c) $(CFLAGS)  -o $@ TestProgram/src/mainTestProgram.c

# ----- analogueMeasurement --------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/readingAnalogueSignals.o: $(TARGETDIR_ALL) AnalogueMeasurement/src/readingAnalogueSignals.c
	$(COMPILE.c) $(CFLAGS)  -o $@ AnalogueMeasurement/src/readingAnalogueSignals.c

# ----- settingGainControl ---------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/settingGainControl.o: $(TARGETDIR_ALL) GainControl/src/settingGainControl.c
	$(COMPILE.c) $(CFLAGS)  -o $@ GainControl/src/settingGainControl.c

# ----- digitalDetection -----------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/readingDigitalSignals.o: $(TARGETDIR_ALL) DigitalDetection/src/readingDigitalSignals.c
	$(COMPILE.c) $(CFLAGS)  -o $@ DigitalDetection/src/readingDigitalSignals.c

# ----- sampleSoftware -----------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/mainSampleSoftware.o: $(TARGETDIR_ALL) SampleSoftware/src/mainSampleSoftware.c
	$(COMPILE.c) $(CFLAGS)  -o $@ SampleSoftware/src/mainSampleSoftware.c

# ----- sampleSoftware -----------------------------------------------------------------------------------------
$(TARGETDIR_ALL)/radarVisual.o: $(TARGETDIR_ALL) Visual/src/radarVisual.c
	$(COMPILE.c) $(GTKLIB) $(CFLAGS)  -o $@ Visual/src/radarVisual.c
	
# ----------------------------------------------------------------------------------------------------------------
#    Clean target deletes all generated files ####
# ----------------------------------------------------------------------------------------------------------------
clean:
	rm -f	$(TARGETDIR_ALL)/testProgram \
		$(TARGETDIR_ALL)/analogueMeasurement \
		$(TARGETDIR_ALL)/gainControl \
		$(TARGETDIR_ALL)/digitalDetection \
		$(TARGETDIR_ALL)/sampleSoftware \
		$(TARGETDIR_ALL)/radarVisual \
		$(TARGETDIR_ALL)/*.o


# Create the target directory (if needed)
$(TARGETDIR_ALL):
	mkdir -p $(TARGETDIR_ALL)


# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-x86_64-Linux

