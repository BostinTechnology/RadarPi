/* 
 * File:   icogLs1Functions.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 01 February 2020, 10:49
 * 
 * Example code for reading and setting data for the light iCog
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../inc/rdr_i2c_comms.h"
#include "../inc/icogLs1Functions.h"


int icogI2CInitialisation (int *i2cbus) {
    
    printf("Into iCog Initialisation\n");
    int status = ICOG_EXIT_SUCCESS;
    printf(".\n");
    status = I2CInitialisation(i2cbus, ICOG_ADDRESS);
    
    printf("iCog Init:%d\n", *i2cbus);
    if (status != I2C_ERR_NONE) {
        printf("I2C Initialisation error\n");
        status = ICOG_SETUP_ERROR;
    }
    
    return status;
};

int icogI2CEnd(void) {
    
    int     status;
    status = I2CEnd();
    
    return status;
};

int icogTurnOffSensor(int *i2cbus) {
    
    int     status;
    int     mask;
    int     shift;
    int     mode;
    int     towrite;
    int     *byte = malloc (sizeof(int*));
    
    printf("Into iCog Turn Off Sensor\n");
    
    mask = 0b11100000;
    shift = 5;
    mode = 0b000;
    
    status = I2CRead(i2cbus, COMMAND_I_REGISTER, byte);
    printf("Command Register Before turning off (0x00):%d\n", *byte);
    if ((*byte & mask) != (mode << shift)) {
        // Modify the register to set bits 7 to 5= 0b000
        towrite = ((*byte & ~mask) | (mode << shift));
        printf("Byte to write to turn off %d\n", towrite);
        status = I2CWrite(i2cbus, COMMAND_I_REGISTER, (int*)towrite, 1);
        usleep(WAITTIME);
        status = I2CRead(i2cbus, COMMAND_I_REGISTER, byte);
        printf("Command Register After turning off (0x00):%x\n", *byte);
        if ((*byte & mask) == (mode << shift)) {
            printf("Sensor Turned on\n");
        }
        else {
            printf("Sensor Turned off\n");
        };
    } 
    else {
        printf("Sensor already Turned off\n");
    }
    return status;
};

int icogSetALSMode(int *i2cbus) {
    
    int     status;
    int     mask;
    int     shift;
    int     mode;
    int     towrite;
    int     byte = 0; // = malloc (sizeof(int*));
    
    printf("Into iCog Set ALS Mode\n");
    status = 0;
        
    //set bits 5-7 of the Command Register 0x00 to 0b101
    //Sensor will be in ALS mode
    mask = 0b11100000;
    shift = 5;
    mode = 0b101;
    
    status = I2CRead(i2cbus, COMMAND_I_REGISTER, &byte);
    //Segmentation fault before this line
    printf("Command Register Before turning on ALS mode (0x00):%x", byte);
    if ((byte & mask) != (mode << shift)) {
        // Modify the register to set bits 7 to 5 = 0b101
        towrite = ((byte & ~mask) | (mode << shift));
        printf("Byte to write to turn on ALS mode %x", towrite);
        status = I2CWrite(i2cbus, COMMAND_I_REGISTER, (int*)towrite, 1);
        usleep(WAITTIME);
        status = I2CRead(i2cbus, COMMAND_I_REGISTER, &byte);
        printf("Command Register After turning on ALS mode (0x00):%x", byte);
        if ((byte & mask) == (mode << shift)) {
            printf("Sensor Turned on in ALS mode");
        }
        else {
            printf("Sensor Not in ALS mode");
        }
    }
    else {
        printf("Sensor Turned on in ALS mode");
    };        
    return status;
};

int icogSetIRMode(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogSetADCResolution(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogReadDataRegisters(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogReadADCClockCycles(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogReadFSR(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogReadSensorMode(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

int icogCalculateLux(void) {
    int status = 0;
    printf("To Be Implemented.\n");
    return status;
};

