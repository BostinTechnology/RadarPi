
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
	bcm2835_spi_chipSelect(BCM2835_SPI_CS1);
}

CommsRetCode SPiTranscieve(uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen) {

    // Check I have been given teh right data to work with
    if (SPibufLen < 1)
        return ERR_PARAMETERS;
        
    char data_buffer[bufLen];      // USed for both transmit and receive buffers

    // Put data into the transfer buffer
    data_buffer = SPitxBuf;

    // Perform the transfer of bufLen bytes.
    // data_buffer is both teh transmit and receive buffer
    bcm2835_spi_transfer(&data_buffer, SPibufLen);

    // Put the received data back in the rxBuf
    SPirxBuf = data_buffer;

    return ERR_NONE;
}
