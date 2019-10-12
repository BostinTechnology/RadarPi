
/******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  *
  * This software comes with no warrantly and is provided as a demo application
  * for use with the ST25R3911B NFC controller
  *
  * For more information    www.Cogniot.eu
  *
******************************************************************************/

#ifndef RDR_SPI_COMMS
#define RDR_SPI_COMMS
/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */

//#include <cstdlib>
#include <bcm2835.h>        // hardware definition library file
#include <stdio.h>
#include <stdint.h>

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

typedef uint16_t      CommsRetCode;          /* Standard Return Code type from function. */


/*!  SPI clock speed choices as defined in bcm2835.h
	BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period) 
	BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
	BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
	BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
	BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
	BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
	BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
	BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
	BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
	BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
	BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
	BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
	BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
	BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
	BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
	BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
	BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
*/

/*!  SPI data mode choices as defined in bcm2835.h
	BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
	BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
	BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
	BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
*/

/*! SPi pin selections as defined in bcm2835.h
	BCM2835_SPI_CS0 = 0			Chip select 0
	BCM2835_SPI_CS1 = 1			Chip select 1
	BCM2835_SPI_CS2 = 2			Chip Select 2 (ie pins CS1 and CS2 are asserted)     
	BCM2835_SPI_CS_NONE = 3		No CS, control it yourself 
 */

/*! SPi bit order as defined in bcm2835.h
	BCM2835_SPI_BIT_ORDER_LSBFIRST	= 0			SPi bit order, LSB first
	BCM2835_SPI_BIT_ORDER_MSBFIRST	= 1			SPi bit order, MSB first
 */

enum CommsRetCodeENUM {
    SPI_ERR_NONE                            =  0, /*! No error occurred */
    SPI_ERR_INITIALISATION                  =  1, /*! Unable to initialise the SPI comms */
    SPI_ERR_COMMS                           =  2, /*! Communications failure has occurred */
    SPI_ERR_PARAMETERS                      =  3, /*! Incorrect parameters provided to the function */

};


/*!
 *****************************************************************************
 * Overview:  Setup the SPi for comms
 *  
 * Utilising the bcm2835 libraries, setup the SPI port for use, see comments 
 * above for information or bcm2835.h
 *
 * param[in]	clock_divider	: SPI clock speed choices
 * param[in]	spi_data_mode	: SPI data mode choices
 * param[in]	bit_order		: SPI bit order, lsb or msb first
 * param[in]	cs_pin			: SPi CS Pin control
 *
 * return ERR_NONE              : No error
 * return ERR_INITILISATION     : Initialisation Error
 *****************************************************************************
 */
CommsRetCode SPiInitialisation(int clock_divider, int spi_data_mode, int bit_order, int cs_pin);



/*!
 *****************************************************************************
 * Overview:  Perform a SPi comms transmit and receive
 *  
 * Utilising the bcm2835 libraries, perform a transmit and receive of data provided.
 * Assumption is the transmit and receive buffers are the same length as defined in
 * the parameters provided
 * 
 * param[in]  *txBuf : The data to be transmitted 
 * param[out] *rxBuf : The data that has been received
 * param[in]  SPibufLen : The length of the transmit AND receive buffers
 *
 * return ERR_NONE              : No error
 * return ERR_INITILISATION     : Initialisation Error
 * return ERR_COMMS             : Comms failure
 *****************************************************************************
 */

CommsRetCode SPiTranscieve(uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen);

/*!
 *****************************************************************************
 * Overview:  Perform a SPi comms transmit only
 *  
 * Utilising the bcm2835 libraries, perform a transmit of data provided.
 * 
 * param[in]  *txBuf : The data to be transmitted 
 * param[in]  SpibufLen : The length of the transmit buffer
 *
 * return ERR_NONE              : No error
 * return ERR_INITILISATION     : Initialisation Error
 * return ERR_COMMS             : Comms failure
 *****************************************************************************
 */
CommsRetCode SPiTransmit(uint8_t *SPitxBuf, uint8_t SPibufLen);

/*!
 *****************************************************************************
 * Overview:  Close the SPi comms port
 *  
 * Utilising the bcm2835 libraries, close the SPi port and return the pins to 
 * the default state.
 * 
 * param[in]  ?? : none
 *
 * return ERR_NONE              : No error
 * return ERR_INITILISATION     : Initialisation Error
 * return ERR_COMMS             : Comms failure
 *****************************************************************************
 */
CommsRetCode SPiEnd(void);


#endif /*RDR_SPI_COMMS */
