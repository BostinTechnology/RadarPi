
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
#include <stdlib.h>
#include <unistd.h>

#include "../../common/inc/radar.h"



/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

// Creates a dataset that includes a frequency float value and a time based time value
struct readings {
    int     element;
    float   frequency;
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
    printf("*              Digital Detection              *\n");
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

    fprintf(lp, "set title \"Frequency\"\n");
    fprintf(lp, "set xlabel \"Time (ticks)\"\n");
    fprintf(lp, "set ylabel \"Frequency (Hz)\"\n");
    fprintf(lp, "set key off\n");
    fprintf(lp, "set yrange [0:500]\n");

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

/*!**************************************************************************
 * Overview: Menu function for user selection of the GPIO pin
 *  
 * Description: This method provides the user with a menu of choice to choose
 *				which GPIO pin is to be measured
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		gpio_pin    : GPIO pin
 *				0			: zero if no pin selected
 *****************************************************************************/

int chooseGPIOPin(void) {

	int		chosen_pin = 0;			// the GPIO pin selected, zero if not chosen
	char	option;
	char	manual_no[5];
	
	printf("Please choose which GPIO Pin to measure\n");
	printf("1 - Digital Signal\n");
	printf("2 - O/P to Pi (with Gain)\n");
	printf("3 - Manual Entry\n");
	printf("e - Return to main menu\n");
	
	option = getchar();
	switch (option)	{
		case '1':
			chosen_pin = IF_OUT_DIGITAL;
			break;
		case '2':
			chosen_pin = IF_OUT_TO_PI;
			break;
		case '3':
			printf("Please enter the GPIO number:\n");
			fgets(manual_no, 5, stdin);
			chosen_pin = atoi(manual_no);
			break;
		case 'e':
			chosen_pin=0;
			break;
	};
	return chosen_pin;
};



/*************************************************************************/
void readValuesContinously(void)
{
	int		pin;
    printf("DEBUG: Into read Values Continously\n");
    float           frequency;
    int     status;
	
	pin = chooseGPIOPin();
	
	setupGpioFunctions();
	
	setSampleHoldForRun();

    printf("Reading Values\n");
    do
    {
        status = returnFullFrequency(&frequency, pin);
        printf("Output of Frequency:%f\n", frequency);
    } while (status != 0);
    
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
    float			frequency=0.0;
    int         max_readings=2000;
    //float       dataset[max_readings][2];           // dataset is 2000 readings by 2 values (frequency and time)
    int         i=0, pin;
    struct		readings dataset[max_readings];
    FILE        *gnu_plot = prepare_plot();         // create instance for plotting
    int         status;

	pin = chooseGPIOPin();

	setupGpioFunctions();
	
	setSampleHoldForRun();
	
    printf("Creating dataset of values...\n");

    testcurrenttime = clock();                       // capture the test start time
    testendtime = testcurrenttime + (testduration * CLOCKS_PER_SEC);

    do {
        
        testcurrenttime = clock();
        status = returnFullFrequency(&frequency, pin);
        if (status == 0) {
            dataset[i].element = i;
            dataset[i].frequency = frequency;
            dataset[i].readtime = testcurrenttime;
            //printf("Dataset:%d  Test Time:%ld  frequency:%d\n", dataset[i].element, dataset[i].readtime, dataset[i].frequency);
            i++;
        }
    } while ((testcurrenttime < testendtime) & (i < max_readings));

    for (i=0; i < max_readings; i = i + 50) {
        printf("Frequency:%lf  Time:%ld\n", dataset[i].frequency, dataset[i].readtime);
    }

    for (i=0; i < max_readings; i++) {
        add_data_to_plot(gnu_plot, dataset[i].readtime, dataset[i].frequency, i);
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

    // main menu
    do {
        printf(" \n\n");
        printf("**************************************************************************\n");
        printf("Available commands: -\n\n");
        printf("c - Read Frequency Continuously\n");
        printf("d - Create dataset of Frequency & time for 30 seconds\n");
        printf("e - Exit program \n");
        printf("\n");

        printf("Please select command -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character


        switch (option)
        {
            case 'c':
                /* Read frequency continuously */
                printf("Reading Values...\n");
                readValuesContinously();
                break;

            case 'd':
                /* Create a dataset of frequency and time for 30 seconds */
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
