
 /******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  * 
  * Sets the Gain Control to 10
  *
  * This software comes with no warrently and is provided as a demo application
  * for use with the Bostin Technology RadarPi
  *
  * For more information    www.Cogniot.eu
  *
  ******************************************************************************/

 /**********************************************************************
  * Development Notes
  *
  * This is a write-only interface, no data is returned
  *
  * Initial Comms by bringing CS low, clock in on the rising edge
  * Requires Clock Polarity (CPOL) = 0 & Clock Phase (CPHA) = 0
  *     MAX Clock Frequency is 5MHz
  *
  * CS Pin is connected to CE1
  *
  * Data is written LSB First
  * 
  * Format for the Gain Register
  *
  * D7   D6   D5   D4  D3  D2  D1  D0
  * SHDN MEAS  X   G3  G2  G1  G0  SEL=1 
  *
  * SHDN is set to 0 for normal operation
  * MEAS is set to 0 for normal operation
  * G3-0 are set to 0b0001 for a gain of 10
  * SEL is set to 1 for Gain Register
  * 
  */

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <bcm2835.h>        // hardware definition library file
#include <time.h>           // to enable time functions
#include "../inc/spi_comms.h"


/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

// Creates a dataset that includes a voltage float value and a time based time value
struct readings {
    int     element;
    float   voltage;
    time_t  readtime;
} ;

/*
******************************************************************************
* GLOBAL TYPES
******************************************************************************
*/




/*
 ******************************************************************************
 * LOCAL VARIABLES
 ******************************************************************************
 */

/*!
 *****************************************************************************
 * Overview:  Display the Bostin Technology introduction screen
 *  
 * This method displays the splash screen
 *
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
int splashscreen(void)
{
    printf("\n***********************************************\n");
    printf("*             Bostin Technology               *\n");
    printf("*                                             *\n");
    printf("*                NFC2 Reader                  *\n");
    printf("*                                             *\n");
    printf("*           Based on the ST25R3911B           *\n");
    printf("*             demo provided by ST             *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return (0);
}

/*!
 *****************************************************************************
 * Overview:  Sets the Gain Control to 10
 *  
 * This method using the SPi comms to send the required data byte to set the
 * gain control to 10
 *
 * Gain Register setting is described above
 *
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void setGainControl(void) {

    uint8_t         msgLen = 1;               // The length of the message 
    uint8_t         txBuf[msgLen];            // The outgoing message
    CommsRetCode   ret;
    
    //printf("DEBUG: Into read Voltage\n");

    // Test to see if works
    txBuf[0] = 0x0F;
    // The line below is the original setting for a gain of 10
    // txBuf[0] = 0x03; //0b00000011 0x03       see above for explanation

    ret = SPiTransmit( txBuf, msgLen);

    return;
}


/******************************************************************************
 *
 * Main Entry function
 *
 * ***************************************************************************/

int main(int argc, char** argv) {

    char option;                        // Used for menu choices

    SPiInitialisation();
    // main menu

    printf(" \n\n");
    printf("**************************************************************************\n");
    printf("Setting Gain Control to ??\n\n");


    printf("Please Enter to configure ");

    getchar();  // have to press enter and this consumes the enter character

    setGainControl();
    
    return 0;
}
