
 /******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  * 
  * Reads and decodes the analogue signals received for the Radar module
  *
  * This software comes with no warrntly and is provided as a demo application
  * for use with the Bostin Technology RadarPi
  *
  * For more information    www.Cogniot.eu
  *
  ******************************************************************************/

 

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

#include "../../common/inc/radar.h"


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
    fprintf(lp, "set yrange [0:3.5]\n");

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

    adcSPiInitialisation();
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
