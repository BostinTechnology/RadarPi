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
    int     byte = 0;
    
    printf("Into iCog Turn Off Sensor\n");
    
    mask = 0b11100000;
    shift = 5;
    mode = 0b000;
    
    status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
    printf("Command Register Before turning off (0x00):%d\n", byte);
    if ((byte & mask) != (mode << shift)) {
        // Modify the register to set bits 7 to 5= 0b000
        towrite = ((byte & ~mask) | (mode << shift));
        printf("Byte to write to turn off %d\n", towrite);
        status = I2CByteWrite(i2cbus, COMMAND_I_REGISTER, towrite);
        usleep(WAITTIME);
        status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
        printf("Command Register After turning off (0x00):%x\n", byte);
        if ((byte & mask) == (mode << shift)) {
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

int icogSetALSContinuousMode(int *i2cbus) {
    
    int     status;
    int     mask;
    int     shift;
    int     mode;
    int     towrite;
    int     byte = 0;
    
    printf("Into iCog Set ALS Mode\n");
    status = 0;
        
    //set bits 5-7 of the Command Register 0x00 to 0b101
    //Sensor will be in ALS mode
    mask = 0b11100000;
    shift = 5;
    mode = 0b101;
    
    status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
    printf("Command Register Before turning on ALS mode (0x00):%x\n", byte);
    if ((byte & mask) != (mode << shift)) {
        // Modify the register to set bits 7 to 5 = 0b101
        towrite = ((byte & ~mask) | (mode << shift));
        printf("Byte to write to turn on ALS mode:%x\n", towrite);
        status = I2CByteWrite(i2cbus, COMMAND_I_REGISTER, towrite);
        usleep(WAITTIME);
        status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
        printf("Command Register After turning on ALS mode (0x00):%x\n", byte);
        if ((byte & mask) == (mode << shift)) {
            printf("Sensor Turned on in ALS mode\n");
        }
        else {
            printf("Sensor Not in ALS mode\n");
        }
    }
    else {
        printf("Sensor already in ALS mode\n");
    };        
    return status;
};

int icogSetIRContinuousMode(int *i2cbus) {
    int     status;
    int     mask;
    int     shift;
    int     mode;
    int     towrite;
    int     byte = 0;
    
    printf("Into iCog Set IR Mode\n");
    status = 0;
        
    //set bits 5-7 of the Command Register 0x00 to 0b101
    //Sensor will be in ALS mode
    mask = 0b11100000;
    shift = 5;
    mode = 0b110;
    
    status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
    printf("Command Register Before turning on IR mode (0x00):%x\n", byte);
    if ((byte & mask) != (mode << shift)) {
        // Modify the register to set bits 7 to 5 = 0b101
        towrite = ((byte & ~mask) | (mode << shift));
        printf("Byte to write to turn on IR mode:%x\n", towrite);
        status = I2CByteWrite(i2cbus, COMMAND_I_REGISTER, towrite);
        usleep(WAITTIME);
        status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
        printf("Command Register After turning on IR mode (0x00):%x\n", byte);
        if ((byte & mask) == (mode << shift)) {
            printf("Sensor Turned on in IR mode\n");
        }
        else {
            printf("Sensor Not in IR mode\n");
        }
    }
    else {
        printf("Sensor already in IR mode\n");
    };
    return status;
};

int icogSetADCResolution(int *i2cbus, int resolution) {
    
    int     status;
    int     mask;
    int     shift;
    int     towrite;
    int     byte = 0;
    
    printf("Into iCog Set ADC Resolution\n");
    status = 0;

    mask = 0b00001100;
    shift = 2;
    
    status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
    printf("Command Register Before setting the ADC Resolution:%x\n", byte);
    if ((byte & mask) != (resolution << shift)) {
        // Modify the register to set bits 7 to 5 = 0b101
        towrite = ((byte & ~mask) | (resolution << shift));
        printf("Byte to write to set ADC Resolution:%x\n", towrite);
        status = I2CByteWrite(i2cbus, COMMAND_II_REGISTER, towrite);
        usleep(WAITTIME);
        status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
        printf("Command Register After setting ADC Resolution:%x\n", byte);
        if ((byte & mask) == (resolution << shift)) {
            printf("ADC Resolution Set\n");
        }
        else {
            printf("ADC Resolution NOT Set\n");
        }
    }
    else {
        printf("ADC Resolution already set\n");
    };      
    return status;
};

int icogSetFSRRange(int *i2cbus, int fsrrange) {

    int     status;
    int     mask;
    int     towrite;
    int     byte = 0;
    
    printf("Into iCog Set Full Scale Range\n");
    status = 0;

    mask = 0b00000011;
    
    status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
    printf("Command Register Before setting the FSR:%x\n", byte);
    if ((byte & mask) != fsrrange) {
        // Modify the register to set bits 7 to 5 = 0b101
        towrite = ((byte & ~mask) | fsrrange);
        printf("Byte to write to set FSR:%x\n", towrite);
        status = I2CByteWrite(i2cbus, COMMAND_II_REGISTER, towrite);
        usleep(WAITTIME);
        status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
        printf("Command Register After setting FSR:%x\n", byte);
        if ((byte & mask) == fsrrange) {
            printf("Full Scale Range Set\n");
        }
        else {
            printf("Full Scale Range NOT Set\n");
        }
    }
    else {
        printf("Full Scale Range already set\n");
    };
    return status;
}

int icogReadDataRegisters(int *i2cbus, int *reading) {
    
    int     status = ICOG_EXIT_SUCCESS;
    int     data_l = 0, data_h = 0;

    printf("In Read Data Registers\n");
    
    status = I2CByteRead(i2cbus, DATA_REGISTER_LOW, &data_l);
    if (status == ICOG_EXIT_SUCCESS) {
        status = I2CByteRead(i2cbus, DATA_REGISTER_HIGH, &data_h);
        printf("Data Register values (0x03/0x02):%x /%x\n", data_h, data_l);
        if (status == ICOG_EXIT_SUCCESS) {
            *reading = (data_h << 8) + data_l;
            printf("Data Register combined %x\n", *reading);
            status = ICOG_EXIT_SUCCESS;
        }
        else {
            status = ICOG_READ_ERROR;
        }
    }
    else {
        status = ICOG_READ_ERROR;
    }
    return status;
};

int icogReadADCResolution(int *i2cbus, int *resolution) {
    
    int     status = ICOG_EXIT_SUCCESS;
    int     mask;
    int     byte;
    int     shift;
    int     adc = 0;
    
    printf("In Read ADC Clock Cycles\n");
    
    mask = 0b00001100;
    shift = 2;

    status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
    printf("ADC Data Resolution reading (bits 2 & 3 of 0x01):%x\n", byte);
    if (status != ICOG_EXIT_SUCCESS) {
        status = ICOG_READ_ERROR;
    }
    else {
        //Decode the values
        adc = (byte & mask) >> shift;
        printf("ADC Resolution Bit %d\n", adc);
        switch (adc) {
            case 0b00:
                // 2 ^ 16
                *resolution = ICOG_ADC_MODE_2_16;
                break;
            case 0b01:
                // 2 ^ 12
                *resolution = ICOG_ADC_MODE_2_12;
                break;
            case 0b10:
                // 2 ^ 8
                *resolution = ICOG_ADC_MODE_2_8;
                break;
            case 0b11:
                // 2 ^ 4
                *resolution = ICOG_ADC_MODE_2_4;
                break;
            default:
                printf("Unable to retrieve ADC Resolution\n");
                status = ICOG_READ_ERROR;
                *resolution= 0;
        }
    }
    printf("ADC Resolution:%d\n", *resolution);
    return status;
};

int icogReadSensorMode(int *i2cbus, int *sensormode) {
    
    int     status = 0;
    int     byte = 0;
    int     omb;
    int     mask;
    int     shift;
    int     mode = 0;
    
    
    printf("In iCog Read Sensor Mode\n");
    mask = 0b11100000;
    shift = 5;

    status = I2CByteRead(i2cbus, COMMAND_I_REGISTER, &byte);
    printf("Sensor Mode Register setting (0x00):%x\n", byte);
    if (status != ICOG_EXIT_SUCCESS) {
        status = ICOG_READ_ERROR;
    }
    else {
        status = ICOG_EXIT_SUCCESS;
        // Operation Mode Bits
        omb = (byte & mask) >> shift;
        printf("Operation Mode Bits %x\n",omb);
        switch (omb) {
            case 0b000:
                mode = 0;
                break;
            case 0b001:
                mode = ICOG_AMBIENT_MODE;
                break;
            case 0b010:
                mode = ICOG_INFRARED_MODE;
                break;
            case 0b101:
                mode = ICOG_AMBIENT_MODE;
                break;
            case 0b110:
                mode = ICOG_INFRARED_MODE;
                break;
            default:
                mode = 0;
        };
    };
    printf("Sensor Mode of Operation :%d\n",mode);
    return status;
};

int icogReadFSR(int *i2cbus, int *fsrvalue) {
    
    int     status = 0;
    int     mask;
    int     byte = 0;
    int     fcr;
    int     opmode = 0;
    
    printf("In iCog Read FSR Routine\n");
    
    mask = 0b00000011;

    status = icogReadSensorMode(i2cbus, &opmode);
    if (status != ICOG_EXIT_SUCCESS) {
        status = ICOG_READ_ERROR;
        *fsrvalue = 0;
    }
    else {
        if (opmode == ICOG_INFRARED_MODE) {
            printf("Full Scale Range mode is IR, returning 65535\n");
            *fsrvalue = ICOG_FSR_READING_MAX;
            status = ICOG_EXIT_SUCCESS;
        }
        else {
            // retrieve data and decode
            status = I2CByteRead(i2cbus, COMMAND_II_REGISTER, &byte);
            if (status != ICOG_EXIT_SUCCESS) {
                status = ICOG_READ_ERROR;
                *fsrvalue = 0;
            }
            else {
                printf("Full Scale Range reading:%x\n", byte);

                // Full Scale Range bits
                fcr = (byte & mask);
                printf("Full Scale Range Selection %d\n",fcr);
                *fsrvalue = 0;
                switch (fcr) {
                    case 0b00:
                        // Range 1
                        *fsrvalue = ICOG_FSR_READING_1K;
                        break;
                    case 0b01:
                        // Range 2
                        *fsrvalue = ICOG_FSR_READING_4K;
                        break;
                    case 0b10:
                        // Range 3
                        *fsrvalue = ICOG_FSR_READING_16K;
                        break;
                    case 0b11:
                        // Range 4
                        *fsrvalue = ICOG_FSR_READING_64K;
                        break;
                };
            };
        };
    };
    printf("Full Scale Range (in ALS mode) value : %d\n", *fsrvalue);
    return status;
};

int icogCalculateLux(int *i2cbus, float *luxvalue) {
    int     status = 0;
    int     fullscale = 0;
    int     adcres = 0;
    int     data = 0;
    float   answer = 0.0;
    
    printf("iCog Calculate Lux Value\n");
    
    // calculate and return the Lux value
    *luxvalue = 0;
    status = icogReadFSR(i2cbus, &fullscale);
    if (status != ICOG_EXIT_SUCCESS) {
        status = ICOG_READ_ERROR;
        *luxvalue = 0;
    }
    else {
        status = icogReadADCResolution(i2cbus, &adcres);
        if (status != ICOG_EXIT_SUCCESS) {
            status = ICOG_READ_ERROR;
            *luxvalue = 0;
        }
        else {
            status = icogReadDataRegisters(i2cbus, &data);
            if (status != ICOG_EXIT_SUCCESS) {
                status = ICOG_READ_ERROR;
                *luxvalue = 0;
            }
            else {
                // Calculate Lux
                printf("Full Scale:%d, ADC Resolution:%d, Data:%d\n", fullscale, adcres, data);
                *luxvalue = (fullscale / (float)adcres) * data;
            };
        };
    };
    printf("Calculated LUX Value: %f\n", *luxvalue);
    
    return status;
};

int icogFastCalculateLux(int *i2cbus, int fsrvalue, int adcres, float *luxvalue) {
    
    int     status = 0;
    int     data = 0;
    
    printf("In iCog Fast Calculation of Lux\n");
    status = icogReadDataRegisters(i2cbus, &data);
    if (status != ICOG_EXIT_SUCCESS) {
        status = ICOG_READ_ERROR;
        *luxvalue = 0;
    }
    else {
        // Calculate Lux
        *luxvalue = (fsrvalue / adcres) * data;
        status = ICOG_EXIT_SUCCESS;
    };
    
    return status;
}
