/* 
 * File:   icogLs1Functions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 01 February 2020, 10:47
 * 
 * Example code for the Ls1 Light iCog
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#ifndef ICOGLS1FUNCTIONS_H
#define ICOGLS1FUNCTIONS_H

// Addresses of device
#define     ICOG_ADDRESS                0x44        //there is also the id_iot chip and the HAT chip
#define     ID_IOT_ADDRESS              0x60        // Address of the EEPROM chip on the board


// Register values
#define     COMMAND_I_REGISTER          0x00
#define     COMMAND_II_REGISTER         0x01

// Parameters
#define     WAITTIME                250             // The time in mS between write and subsequent read

// The list below is the failure modes possible
#define     ICOG_EXIT_SUCCESS        0
#define     ICOG_NO_RESPONSE         1
#define     ICOG_SETUP_ERROR         2


/*!***************************************************************************
 * Overview:  Initialises the I2C port for the iCog
 *  
 * This method using the Wiring Pi library to set the required settings to set the
 * I2C port for the iCog Control chip
 *
 * param[in] *i2cbus :  Nothing
 *
 * return status     : ICOG_SETUP_ERROR
 *                   : ICOG_EXIT_SUCCESS
 *        i2cbus     : The file handler for the device
 ******************************************************************************/
int icogI2CInitialisation (uint8_t *i2cbus);

/*!***************************************************************************
 * Overview:  Ends the I2C port for the iCog  Control
 *  
 * This method releases the I2C port for the iCog
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogI2CEnd(void);

/*!***************************************************************************
 * Overview:  Turns off the iCog sensor
 *  
 * This method turns off the light sensor part of the iCog
 *      Set bits 5-7 of the Command Register 0x00 to 0
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogTurnOffSensor(uint8_t *i2cbus);

/*!***************************************************************************
 * Overview:  Sets the Light iCog into Ambient Light Sensing (ALS) mode
 *  
 * This method turns the light sensor into ALS mode.
 *      When the iCog is programmed for ambient light sensing, the ambient light
 *      with wavelength within the “Ambient Light Sensing” spectral response 
 *      curve is measured. With ADC, the current is converted to an unsigned 
 *      n-bit (up to 16 bits) digital output.
 *
 * param[in] i2cbus : A pointer to the bus ID 
 *
 * return none   : nothing
 ******************************************************************************/
int icogSetALSMode(void);

/*!***************************************************************************
 * Overview:  Sets the Light iCog into Infra Red (IR) mode
 *  
 * This method turns the iCog into IR Mode.
 *      When the part is programmed for infrared (IR) sensing, the IR light 
 *      with wavelength within the “IR Sensing” spectral response curve is 
 *      measured. With ADC, the current is converted to an unsigned n-bit 
 *      (up to 16-bits) digital output.
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogSetIRMode(void);

/*!***************************************************************************
 * Overview:  Sets the Light iCog into Infra Red (IR) mode
 *  
 * This sets the ADC Resolution and the number of clock cycles per conversion
 *      of the iCog. Changing the number of clock cycles does more than just
 *      change the resolution of the device; it also changes the integration
 *      time, which is the period the device’s analog-to-digital (A/D) converter
 *      samples the photodiode current signal for a measurement. The ONLY 16-bit
 *      ADC resolution is capable of rejecting 50Hz and 60Hz flicker caused by
 *      artificial light sources. Table 9 lists the possible ADC resolution.
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogSetADCResolution(void);

/*!***************************************************************************
 * Overview:  Reads the data registers from the iCog
 *  
 * This method reads both of the registers and returns the value regardless
 *      of the data resolution
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogReadDataRegisters(void);

/*!***************************************************************************
 * Overview:  Reads the ADC Resolution from the iCog and returns the number of
 *            clock cycles per conversion
 *  
 * This method reads the ADC resolution and returns the value in terms of the 
 * B3   B2      NUMBER OF CLOCK CYCLES      n-BIT ADC
 *  0   0       216 = 65,536                16
 *  0   1       212 = 4,096                 12
 *  1   0       28 = 256                    8
 *  1   1       24 = 16                     4
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogReadADCClockCycles(void);

/*!***************************************************************************
 * Overview:  Reads the Full Scale Range (FSR) from the iCog and returns the
 *            maximum lux value obtainable
 *  
 * This method reads the Full Scale Range (FSR) has four different selectable 
 * ranges. Each range has a maximum allowable lux value. Higher range values 
 * offer wider ALS lux value. Table 8 lists the possible values of FSR.
 * B0   B1  k   RANGE(k)    FSR (LUX) @ ALS SENSING     FSR @ IR SENSING
 * 0    0   1   Range1              1,000                   65535
 * 0    1   2   Range2              4,000                   65535
 * 1    0   3   Range3              16,000                  65535
 * 1    1   4   Range4              64,000                  65535
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogReadADCClockCycles(void);

/*!***************************************************************************
 * Overview:  Reads the Sensor Operating mode from the iCog and returns it.
 *  
 * This method reads the sensor operating mode and returns it
 * B7   B6  B5      OPERATION   
 * 0    0   0       Power-down the device (Default)
 * 0    0   1       The IC measures ALS only once every integration cycle. 
 *                      This is the lowest operating mode.
 * 0    1   0       IR once
 * 0    1   1       Reserved (DO NOT USE)
 * 1    0   0       Reserved (DO NOT USE)
 * 1    0   1       The IC measures ALS continuously
 * 1    1   0       The IC measures IR continuous
 * 1    1   1       Reserved (DO NOT USE) 
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogReadSensorMode(void);

/*!***************************************************************************
 * Overview:  Reads the various registers from the iCog to calculate the Lux value
 *  
 * This method reads all the various registers and returns the Lux value
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 ******************************************************************************/
int icogCalculateLux(void);


#endif /* ICOGLS1FUNCTIONS_H */

