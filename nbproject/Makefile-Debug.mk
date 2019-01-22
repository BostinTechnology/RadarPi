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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/TestProgram/src/adcTest.o \
	${OBJECTDIR}/TestProgram/src/freqTest.o \
	${OBJECTDIR}/TestProgram/src/gainTest.o \
	${OBJECTDIR}/TestProgram/src/ledTest.o \
	${OBJECTDIR}/TestProgram/src/mainTestProgram.o \
	${OBJECTDIR}/common/src/adcFunctions.o \
	${OBJECTDIR}/common/src/gainFunctions.o \
	${OBJECTDIR}/common/src/gpioFunctions.o \
	${OBJECTDIR}/common/src/ledControl.o \
	${OBJECTDIR}/common/src/utilities.o \
	${OBJECTDIR}/gpio_control.o \
	${OBJECTDIR}/radar.o


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

${OBJECTDIR}/TestProgram/src/adcTest.o: TestProgram/src/adcTest.c 
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/adcTest.o TestProgram/src/adcTest.c

${OBJECTDIR}/TestProgram/src/freqTest.o: TestProgram/src/freqTest.c 
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/freqTest.o TestProgram/src/freqTest.c

${OBJECTDIR}/TestProgram/src/gainTest.o: TestProgram/src/gainTest.c 
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/gainTest.o TestProgram/src/gainTest.c

${OBJECTDIR}/TestProgram/src/ledTest.o: TestProgram/src/ledTest.c 
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/ledTest.o TestProgram/src/ledTest.c

${OBJECTDIR}/TestProgram/src/mainTestProgram.o: TestProgram/src/mainTestProgram.c 
	${MKDIR} -p ${OBJECTDIR}/TestProgram/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TestProgram/src/mainTestProgram.o TestProgram/src/mainTestProgram.c

${OBJECTDIR}/common/src/adcFunctions.o: common/src/adcFunctions.c 
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/adcFunctions.o common/src/adcFunctions.c

${OBJECTDIR}/common/src/gainFunctions.o: common/src/gainFunctions.c 
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/gainFunctions.o common/src/gainFunctions.c

${OBJECTDIR}/common/src/gpioFunctions.o: common/src/gpioFunctions.c 
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/gpioFunctions.o common/src/gpioFunctions.c

${OBJECTDIR}/common/src/ledControl.o: common/src/ledControl.c 
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/ledControl.o common/src/ledControl.c

${OBJECTDIR}/common/src/utilities.o: common/src/utilities.c 
	${MKDIR} -p ${OBJECTDIR}/common/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/common/src/utilities.o common/src/utilities.c

${OBJECTDIR}/gpio_control.o: gpio_control.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/gpio_control.o gpio_control.c

${OBJECTDIR}/radar.o: radar.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -ITestProgram -include TestProgram/inc -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/radar.o radar.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/radarpi

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
