
/******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  *
  * This software comes with no warrently and is provided as a demo application
  * for use with the ST25R3911B NFC controller
  *
  * For more information    www.Cogniot.eu
  *
******************************************************************************/



/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */

//#include <cstdlib>
#include <bcm2835.h>        // hardware definition library file
#include <stdio.h>
#include "../inc/spi_comms.h"

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

CommsRetCode SPiInitialisation(void){
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return ERR_INITIALISATION;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
        return ERR_INITIALISATION;
    }

	//Set SPI clock speed
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096);

	//Set SPI data mode
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE3);		

	//Set with CS pin to use for next transfers
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
}

CommsRetCode SPiTranscieve(uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen) {

    uint8_t     i;
    
    // Check I have been given teh right data to work with
    if (SPibufLen < 1)
    {
        return ERR_PARAMETERS;
    }
        
    char data_buffer[SPibufLen];      // Used for both transmit and receive buffers

    // Put data into the transfer buffer
    for (i=0; i < SPibufLen; i++)
    {
        data_buffer[i] = SPitxBuf[i];
        //printf("SPitxBuf Data In %d : %x\n", i, data_buffer[i]);      // For debug purposes
    }
    //printf("DEBUG: About to perform comms\n");

    // Perform the transfer of bufLen bytes.
    // data_buffer is both the transmit and receive buffer
    bcm2835_spi_transfern(&data_buffer[0], SPibufLen);

    // Put the received data back in the rxBuf
    for (i=0; i < SPibufLen; i++)
    {
        SPirxBuf[i] = data_buffer[i];
        //printf("SPirxBuf Out %d : %x\n", i, SPirxBuf[i]);             // FOr debug purposes
    }
    return ERR_NONE;
}
