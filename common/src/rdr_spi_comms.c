
/******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  *
  * This software comes with no warranty and is provided as a demo application
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
#include "../inc/rdr_spi_comms.h"



CommsRetCode SPiInitialisation(int clock_divider, int spi_data_mode, int bit_order, int cs_pin){
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return SPI_ERR_INITIALISATION;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
        return SPI_ERR_INITIALISATION;
    }

	//Set SPI clock speed
	bcm2835_spi_setClockDivider(clock_divider);

	//Set SPI data mode
	bcm2835_spi_setDataMode(spi_data_mode);
	
	// Set Bit Order
	bcm2835_spi_setBitOrder(bit_order);

	//Set with CS pin to use for next transfers
	bcm2835_spi_chipSelect(cs_pin);
	
	return SPI_ERR_NONE;
}

CommsRetCode SPiTranscieve(uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen) {

    uint8_t     i;
    
    // Check I have been given teh right data to work with
    if (SPibufLen < 1)
    {
        return SPI_ERR_PARAMETERS;
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
    return SPI_ERR_NONE;
};

CommsRetCode SPiTransmit(uint8_t *SPitxBuf, uint8_t SPibufLen) {
    uint8_t     i;
    
    // Check I have been given the right data to work with
    if (SPibufLen < 1)
    {
        return SPI_ERR_PARAMETERS;
    }
        
    char data_buffer[SPibufLen];      // Used for transmit buffer

    // Put data into the transfer buffer
    for (i=0; i < SPibufLen; i++)
    {
        data_buffer[i] = SPitxBuf[i];
        //printf("DEBUG: SPitxBuf Data In %d : %x\n", i, data_buffer[i]);      // For debug purposes
    }
    //printf("DEBUG: About to perform comms\n");

    // Perform the transfer of bufLen bytes.
    // data_buffer is both the transmit and receive buffer
    bcm2835_spi_writenb(&data_buffer[0], SPibufLen);
	
	//printf("DEBUG: Comms Complete\n");

    return SPI_ERR_NONE;
}

CommsRetCode SPiEnd(void) {
	
	bcm2835_spi_end();
	
	return SPI_ERR_NONE;
}