
 /******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  * 
  * Reads and decodes the analogue signals received for the Radar module
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
  * Use leading zero's to get the required number of bits
  *
  * Initial Comms by bringing CS low, clock out on falling edge, data in on the rising edge
  * 
  *     If it is low, it must be brought high and then low to work
  * Format of message to MCP3202
  *     Start Bit               Set to 1
  *     Sgl / Diff bit          Set to 1 for Single Ended
  *     Odd / Sign Bit          Set to 0 as using Channel 0
  *     MSBF                    Set to 1 to as only output MSB first
  *
  * Format of response from MCP3202
  *     Null Bit
  *     B11                 Bits B11 - 8 are in the lower half of the first byte returned
  *     B10
  *     ....                Bits B7 - 0 are in the second byte received
  *     B1
  *     B0
  *
  *     After this further clocks will just output zero's
  *
  * Comms method
  *     0. CS Low
  *     1. Send 0b00000001      Just the start bit as byte 1
  *     2. Send 0b10100000      The message bits above
  *         This will return 8 bits, the last 4 contain the upper half of the reply
  *     3. Send 0b00000000      This is ignoted by the MCP3202
  *         The response is the lower 8 bits of the reply
  *
  *     Merge the upper 4 bits (AND with 0b00001111 << 4) and the lower half together
  *     4. CS High
  *
  * Conversion of the response
  *     voltage read = (value received * 3.3) / 4096
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
    printf("*                  Radar Pi                   *\n");
    printf("*            Analogue Measurement             *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return (0);
}

/*!*********************************************************************
 *
 * Setup the plotting functionality
 *
 * */
FILE *prepare_plot() {

//    FILE *lp;
    
    printf("Preparing Plot\n");

    FILE *lp = popen("gnuplot -persistent", "w");        //persistent ensures it stays on screen when the program completes
                //

    fprintf(lp, "set title \"Voltage Levels\"\n");
    fprintf(lp, "set xlabel \"Time (ticks)\"\n");
    fprintf(lp, "set ylabel \"Voltage (V)\"\n");
    fprintf(lp, "set key off\n");
    fprintf(lp, "set yrange [0:3]\n");

    fprintf(lp, "plot '-' with lines\n");
        
    return lp;

}

/*!*********************************************************************
 *
 * Add a value to the plot
 *
 * */
void add_data_to_plot(FILE *p, float x, float y, int element) {

    //printf("Adding Data:%d\n", element);

    fprintf(p, "%f %f\n", x, y);                    // Adding data to graph

    return;
}

/*!*********************************************************************
 *
 * Execute the plotting functionality
 *
 * */
void execute_plot(FILE *p) {

    printf("Excuting Plot\n");
    
    fprintf(p, "e\n");

    return;
}

/*!*********************************************************************
 *
 * Close the plotting functionality
 *
 * */
void close_plot(FILE *p) {

    printf("Closing Plot\n");
    
    pclose(p);

    return;
}

/*************************************************************************/
float readVoltage(void) {
    uint8_t         msgLen = 3;               // The length of the message 
    uint8_t         txBuf[msgLen];            // The outgoing message
    uint8_t         rxBuf[msgLen];            // The reply from the A-D
    float           reading=0.00;                // The output value
    float           supply_voltage = 3.3;     // SUpply voltage for the A-D
    uint16_t        fsd_range=4096;           // Maximum value from A-D (12 bits)
    CommsRetCode   ret;
    
    //printf("DEBUG: Into read Voltage\n");

    txBuf[0] = 0x01; //0b00000001 - 001                  // Start Bit
    // For Custard Pi 2    txBuf[1] = 0xF0; //0b11110000 - 240                  // Remainder of message to send  
    txBuf[1] = 0xB0; //0b10110000 -                   // Remainder of message to send  
    txBuf[2] = 0x00; //0b00000000 - 000                  // Dummy to get MCP3202 to send return data    

    ret = SPiTranscieve( txBuf, rxBuf, msgLen);

    /* For debug purposes
    printf("Response:");
    for (i=0; i < msgLen; i++)
    {
        printf("%02x", rxBuf[i]);
    }
    printf("\n");
    */

    /* Shift the bits to the correct locatin
     * the first byte back is ignored as it only there for comms
     * the second byte is the MSByte (lower 4 bits anyway, rest are zero)
     * the third byte is the LSByte
     * */
    
    reading = (rxBuf[1] << 8) + rxBuf[2];
    //printf("DEBUG: Reading after merge:%f\n", reading);

    // Formula for calculation      Digital Output Code = 4096 * Vin
    //                                                    ----------
    //                                                       Vdd
    reading = reading * (supply_voltage / fsd_range);

    //printf("DEBUG: Voltage being returned:%f\n", reading);

    return reading;
}

/*************************************************************************/
void readValuesContinously(void)
{
    printf("DEBUG: Into read Values Continously\n");
    float           voltage;

    printf("Reading Values\n");
    do
    {
        voltage = readVoltage();
        printf("Output from A-D:%f\n", voltage);
    } while (1);
    
    return;
}



/*!*********************************************************************
 *
 * read values with timestamp for 30 seconds / 2000 readings
 *
 * */
void createDataset(void) {
    time_t      testendtime, testcurrenttime;
    int         testduration = 10;
    float       voltage=0.00;
    int         max_readings=2000;
    //float       dataset[max_readings][2];           // dataset is 2000 readings by 2 values (voltage and time)
    int         i=0;
    struct readings dataset[max_readings];
    FILE        *gnu_plot = prepare_plot();         // create instance for plotting

    printf("Creating dataset of values...\n");

    testcurrenttime = clock();                       // capture the test start time
    testendtime = testcurrenttime + (testduration * CLOCKS_PER_SEC);

    do {
        
        testcurrenttime = clock();
        voltage = readVoltage();
        dataset[i].element = i;
        dataset[i].voltage = voltage;
        dataset[i].readtime = testcurrenttime;
        //printf("Dataset:%d  Test Time:%ld  Voltage:%f\n", dataset[i].element, dataset[i].readtime, dataset[i].voltage);
        i++;
    } while ((testcurrenttime < testendtime) & (i < max_readings));

    for (i=0; i < max_readings; i = i + 50) {
        printf("Voltage:%f  Time:%ld\n", dataset[i].voltage, dataset[i].readtime);
    }

    for (i=0; i < max_readings; i++) {
        add_data_to_plot(gnu_plot, dataset[i].readtime, dataset[i].voltage, i);
    }
    
    execute_plot(gnu_plot);

    printf("Plot drawn, press any key to continue");

    getchar();

    close_plot(gnu_plot);
    
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
    do {
        printf(" \n\n");
        printf("**************************************************************************\n");
        printf("Available commands: -\n\n");
        printf("c - Read Voltage Continuously\n");
        printf("d - Create dataset of Voltage & time for 30 seconds\n");
        printf("e - Exit program \n");
        printf("\n");

        printf("Please select command -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character


        switch (option)
        {
            case 'c':
                /* Read voltage continuously */
                printf("Reading Values...\n");
                readValuesContinously();
                break;

            case 'd':
                /* Create a dataset of voltage and time for 30 seconds */
                printf("Creating dataset...\n");
                createDataset();

            case 'e':
                printf("Exiting.......\n");
                option = 'e';
                break;

            default:
                printf("Unrecognised command!\n");

       }
       fflush (stdout) ;
    } while(option != 'e');
    
    return 0;
}
