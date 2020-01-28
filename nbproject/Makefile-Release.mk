#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/SampleSoftware/src/mainSampleSoftware.o \
	${OBJECTDIR}/TestProgram/src/adcTest.o \
	${OBJECTDIR}/TestProgram/src/mainTestProgram.o \
	${OBJECTDIR}/common/src/adcFunctions.o \
	${OBJECTDIR}/common/src/gainFunctions.o \
	${OBJECTDIR}/common/src/gpioFunctions.o \
	${OBJECTDIR}/common/src/icogFunctions.o \
	${OBJECTDIR}/common/src/ledControl.o \
	${OBJECTDIR}/common/src/radar.o \
	${OBJECTDIR}/common/src/rdr_i2c_comms.o \
	${OBJECTDIR}/common/src/rdr_utilities.o \
	${OBJECTDIR}/default_header.o \
	${OBJECTDIR}/nbproject/newfile1.o \
	${OBJECTDIR}/nbproject/newfile2.o \
	${OBJECTDIR}/nbproject/newmain.o \
	${OBJECTDIR}/newmain.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/radarpi

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/radarpi: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/radarpi ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/SampleSoftware/src/mainSampleSoftware.o: SampleSoftware/src/mainSampleSoftware.c
	${MKDIR} -p ${OBJECTDIR}/SampleSoftware/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SampleSoftware/src/mainSampleSoftware.o SampleSoftware/src/mainSampleSoftware.c

${OBJECTDIR}/TestProgram/src/adcTest.o: TestProgram/src/adcTest.c
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/adcTest.o TestProgram/src/adcTest.c

${OBJECTDIR}/TestProgram/src/mainTestProgram.o: TestProgram/src/mainTestProgram.c
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/mainTestProgram.o TestProgram/src/mainTestProgram.c

${OBJECTDIR}/common/src/adcFunctions.o: common/src/adcFunctions.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/adcFunctions.o common/src/adcFunctions.c

${OBJECTDIR}/common/src/gainFunctions.o: common/src/gainFunctions.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/gainFunctions.o common/src/gainFunctions.c

${OBJECTDIR}/common/src/gpioFunctions.o: common/src/gpioFunctions.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/gpioFunctions.o common/src/gpioFunctions.c

${OBJECTDIR}/common/src/icogFunctions.o: common/src/icogFunctions.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/icogFunctions.o common/src/icogFunctions.c

${OBJECTDIR}/common/src/ledControl.o: common/src/ledControl.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/ledControl.o common/src/ledControl.c

${OBJECTDIR}/common/src/radar.o: common/src/radar.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/radar.o common/src/radar.c

${OBJECTDIR}/common/src/rdr_i2c_comms.o: common/src/rdr_i2c_comms.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/rdr_i2c_comms.o common/src/rdr_i2c_comms.c

${OBJECTDIR}/common/src/rdr_utilities.o: common/src/rdr_utilities.c
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/rdr_utilities.o common/src/rdr_utilities.c

${OBJECTDIR}/default_header.o: default_header.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/default_header.o default_header.c

${OBJECTDIR}/nbproject/newfile1.o: nbproject/newfile1.c
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/newfile1.o nbproject/newfile1.c

${OBJECTDIR}/nbproject/newfile2.o: nbproject/newfile2.c
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/newfile2.o nbproject/newfile2.c

${OBJECTDIR}/nbproject/newmain.o: nbproject/newmain.c
	${MKDIR} -p ${OBJECTDIR}/nbproject
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/nbproject/newmain.o nbproject/newmain.c

${OBJECTDIR}/newmain.o: newmain.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newmain.o newmain.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
