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
#define     DATA_REGISTER_LOW           0x02
#define     DATA_REGISTER_HIGH          0x03

// Parameters
#define     WAITTIME                250             // The time in mS between write and subsequent read

// The list below is the failure modes possible
#define     ICOG_EXIT_SUCCESS        0
#define     ICOG_NO_RESPONSE         1
#define     ICOG_SETUP_ERROR         2
#define     ICOG_READ_ERROR          3


// Mode Setting values
#define     ICOG_SET_FSR_1K         0b00
#define     ICOG_SET_FSR_4K         0b01
#define     ICOG_SET_FSR_16K        0b10
#define     ICOG_SET_FSR_64K        0b11

#define     ICOG_SET_ADC_16         0b00
#define     ICOG_SET_ADC_12         0b01
#define     ICOG_SET_ADC_8          0b10
#define     ICOG_SET_ADC_4          0b11

#define     ICOG_AMBIENT_MODE       65      // "ALS" mode
#define     ICOG_INFRARED_MODE      73      // "IR" mode

#define     ICOG_ADC_MODE_2_16      65536
#define     ICOG_ADC_MODE_2_12      4096
#define     ICOG_ADC_MODE_2_8       256
#define     ICOG_ADC_MODE_2_4       16

#define     ICOG_FSR_READING_1K     1000
#define     ICOG_FSR_READING_4K     4000
#define     ICOG_FSR_READING_16K    16000
#define     ICOG_FSR_READING_64K    64000
#define     ICOG_FSR_READING_MAX    65535
         
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
int icogI2CInitialisation (int *i2cbus);

/*!***************************************************************************
 * Overview:  Ends the I2C port for the iCog  Control
 *  
 * This method releases the I2C port for the iCog
 *
 * param[in/out] ?? : nothing 
 *
 * return status   : nothing  //ToDo: Set status'
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
 * return status   : nothing    //ToDo: Set status'
 ******************************************************************************/
int icogTurnOffSensor(int *i2cbus);

/*!***************************************************************************
 * Overview:  Sets the Light iCog into Ambient Light Sensing (ALS) mode
 *  
 * This method turns the light sensor into ALS CONTINUOUS mode.
 *      When the iCog is programmed for ambient light sensing, the ambient light
 *      with wavelength within the “Ambient Light Sensing” spectral response 
 *      curve is measured. With ADC, the current is converted to an unsigned 
 *      n-bit (up to 16 bits) digital output.
 *
 * param[in] i2cbus : A pointer to the bus ID 
 *
 * return status   : nothing        //ToDo: Set status'
 ******************************************************************************/
int icogSetALSContinuousMode(int *i2cbus);

/*!***************************************************************************
 * Overview:  Sets the Light iCog into Infra Red (IR) mode
 *  
 * This method turns the iCog into IR CONTINUOUS Mode.
 *      When the part is programmed for infrared (IR) sensing, the IR light 
 *      with wavelength within the “IR Sensing” spectral response curve is 
 *      measured. With ADC, the current is converted to an unsigned n-bit 
 *      (up to 16-bits) digital output.
 *
 * param[in] i2cbus : A pointer to the bus ID 
 *
 * return status   : nothing        //ToDo: Set status'
 ******************************************************************************/
int icogSetIRContinuousMode(int *i2cbus);

/*!***************************************************************************
 * Overview:  Sets the ADC Resolution
 *  
 * This sets the ADC Resolution and the number of clock cycles per conversion
 *      of the iCog. Changing the number of clock cycles does more than just
 *      change the resolution of the device; it also changes the integration
 *      time, which is the period the device’s analog-to-digital (A/D) converter
 *      samples the photodiode current signal for a measurement. The ONLY 16-bit
 *      ADC resolution is capable of rejecting 50Hz and 60Hz flicker caused by
 *      artificial light sources. Table 9 lists the possible ADC resolution.
 *      Setting         B3  B2      NUMBER OF CLOCK CYCLES  n-BIT ADC
 *      ICOG_SET_ADC_16     0   0       216 = 65,536            16
 *      ICOG_SET_ADC_12     0   1       212 = 4,096             12
 *      ICOG_SET_ADC_8      1   0       28 = 256                8
 *      ICOG_SET_ADC_4      1   1       24 = 16                 4
 *
 * param[in] i2cbus : A pointer to the bus ID
 *      [in] resolution : See table above 
 *
 * return status   : //ToDo
 ******************************************************************************/
int icogSetADCResolution(int *i2cbus, int resolution);

/*!***************************************************************************
 * Overview:  Sets the Full Scale Range
 *  
 * This sets the Full Scale Range (FSR) has four different selectable ranges. 
 *      Each range has a maximum allowable lux value. Higher range values offer 
 *      wider ALS lux value. Table 8 lists the possible values of FSR for the 
 *      499kΩ REXT resistor.
 * 
 *      Setting             B0  B1  k   RANGE(k)    FSR(LUX)@ALS SENSING   FSR@IR SENSING
 *      ICOG_SET_FSR_1K     0   0   1   Range1      1,000                   65535
 *      ICOG_SET_FSR_4K     0   1   2   Range2      4,000                   65535
 *      ICOG_SET_FSR_16K    1   0   3   Range3      16,000                  65535
 *      ICOG_SET_FSR_64K    1   1   4   Range4      64,000                  65535
 *
 * param[in] i2cbus     : A pointer to the bus ID
 *      [in] FSRrange   : See table above 
 *
 * return status   : //ToDo
 ******************************************************************************/
int icogSetFSRRange(int *i2cbus, int fsrrange);

/*!***************************************************************************
 * Overview:  Reads the data registers from the iCog
 *  
 * This method reads both of the registers and returns the value regardless
 *      of the data resolution.
 *      The ISL29023 has two 8-bit read-only registers to hold the upper and 
 *      lower byte of the ADC value. The upper byte is accessed at address 0x03 
 *      and the lower byte is accessed at address 0x02. For 16-bit resolution, 
 *      the data is from D0 to D15; for 12-bit resolution, the data is from 
 *      D0 to D11; for 8-bit resolution, the data is from D0 to D7 and 4-bit 
 *      resolution, the data is from D0 to D3. The registers are refreshed after 
 *      every conversion cycle. The default register value is 0x00 at power-on.
 * 
 *      NAME        Reg. Addr   Register Bits                       DFLT
 *                              B7  B6  B5  B4  B3  B2  B1  B0      (Hex)
 *      DATALSB     0x02        D7  D6  D5  D4  D3  D2  D1  D0      0x00
 *      DATAMSB     0x03        D15 D14 D13 D12 D11 D10 D9  D8      0x00
 *
 * param[in] i2cbus     : A pointer to the bus ID
 *      [out] reading   : a pointer for the reading to be stored in 
 *
 * return none   : //ToDo
 ******************************************************************************/
int icogReadDataRegisters(int *i2cbus, int *reading);

/*!***************************************************************************
 * Overview:  Reads the ADC Resolution from the iCog and returns the number of
 *            clock cycles per conversion
 *  
 * This method reads the ADC resolution and returns the value in terms of the 
 *          Mode                    Resolution
 *          ICOG_ADC_MODE_2_16      65536
 *          ICOG_ADC_MODE_2_12      4096
 *          ICOG_ADC_MODE_2_8       256
 *          ICOG_ADC_MODE_2_4       16
 *
 * param[in]  i2cbus     : A pointer to the bus ID 
 *      [out] resolution : Returns resolution
 *
 * return status   : //ToDo
 ******************************************************************************/
int icogReadADCResolution(int *i2cbus, int *resolution);

/*!***************************************************************************
 * Overview:  Reads the Sensor overall Operating mode from the iCog and returns it.
 *  
 * This method reads the sensor overall operating mode and returns the mode, either
 *      ICOG_AMBIENT_MODE           ALS mode
 *      ICOG_INFRARED_MODE          IR mode
 * based on the bits read from the sensor on the table below.
 * 
 *  B7 B6 B5    OPERATION                                   Return Value
 *  0  0  0     Power-down the device (Default)             0
 *  0  0  1     The IC measures ALS only once every         ICOG_AMBIENT_MODE
 *                  integration cycle. 
 *                  This is the lowest operating mode.
 *  0  1  0     IR once                                     ICOG_INFRARED_MODE
 *  0  1  1     Reserved (DO NOT USE)                       0
 *  1  0  0     Reserved (DO NOT USE)                       0
 *  1  0  1     The IC measures ALS continuously            ICOG_AMBIENT_MODE
 *  1  1  0     The IC measures IR continuous               ICOG_INFRARED_MODE
 *  1  1  1     Reserved (DO NOT USE)                       0
 *
 * param[in]  i2cbus     : A pointer to the bus ID 
 *      [out] sensormode : the operating mode defined above   
 *
 * return none   : nothing
 ******************************************************************************/
int icogReadSensorMode(int *i2cbus, int *sensormode);

/*!***************************************************************************
 * Overview:  Reads the Full Scale Range (FSR) from the iCog and returns the
 *            maximum lux value obtainable
 *  
 * This method reads the Full Scale Range (FSR) has four different selectable 
 * ranges. Each range has a maximum allowable lux value. Higher range values 
 * offer wider ALS lux value. The table below lists the possible values of FSR.
 *      Range value             FSR
 *      ICOG_FSR_READING_1K     1000
 *      ICOG_FSR_READING_4K     4000
 *      ICOG_FSR_READING_16K    16000
 *      ICOG_FSR_READING_64K    64000
 *      ICOG_FSR_READING_MAX    65535
 *
 * param[in]  i2cbus     : A pointer to the bus ID 
 *      [out] fsrvalue   : The value from above depending on mode.
 * 
 * return status   : //ToDo
 ******************************************************************************/
int icogReadFSR(int *i2cbus, int *fsrvalue);

/*!***************************************************************************
 * Overview:  Reads the various registers from the iCog to calculate the Lux value
 *  
 * This method reads all the various registers and returns the Lux value. It
 * reads all the registers and data values for each calculation.
 * 
 * The scale of values returned is based on the range selected:
 * - Range1 = 0.015 to 1,000 Lux
 * - Range2 = 0.06 to 4,000 Lux
 * - Range3 = 0.24 to 16,000 Lux
 * - Range4 = 0.96 to 64,000 Lux
 * 
 * Formula for Calculation
 * lux = (full scale range / adc resolution ) * data read back
 *
 * param[in]  i2cbus    : A pointer to the bus ID
 *      [out[ luxvalue  : The Lux reading
 *
 * return none   : nothing
 ******************************************************************************/
int icogCalculateLux(int *i2cbus, float *luxvalue);

/*!***************************************************************************
 * Overview: Similar to icogCalculateLux except it DOESNT read the various 
 *           registers from the iCog to calculate the Lux value
 *  
 * This method ONLY reqds the data register and expects all the various 
 * registers to be provided and returns the Lux value. 
 * 
 * The scale of values returned is based on the range selected:
 * - Range1 = 0.015 to 1,000 Lux
 * - Range2 = 0.06 to 4,000 Lux
 * - Range3 = 0.24 to 16,000 Lux
 * - Range4 = 0.96 to 64,000 Lux
 * 
 * Formula for Calculation
 * lux = (full scale range / adc resolution ) * data read back
 * 
 * param[in]  i2cbus    : A pointer to the bus ID
 *      [in]  fsrvalue  : The FSR value currently set
 *      [in]  adcres    : The ADC resolution currently set
 *      [out[ luxvalue  : The Lux reading
 *
 * return none   : nothing
 ******************************************************************************/
int icogFastCalculateLux(int *i2cbus, int fsrvalue, int adcres, float *luxvalue);


#endif /* ICOGLS1FUNCTIONS_H */

