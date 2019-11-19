
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidVisual.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 30 March 2019, 09:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <math.h>
#include <cairo.h>
#include <unistd.h>
#include <pthread.h>

#include "../inc/radarVisual.h"



/*******************************************************************************
 *
 *  To Do List
 *  ==========
 * ToDo: Reduce screen updating for Ciaran, too much data on screen.
 * 
 * BUGS in Git!!!!
 * 
 * 31   Add in way of knowing it is running or not, a coloured circle maybe.
 * 30   Is it worth changing the Set for gain to set for all Config...
 *          Would need to change the text on screen a little and maybe set it 
 *          to active or greyed out.
 *          Either way the screen needs to be clearer
 * 32   Does the Sample and Hold signal need to be set to run for all modes, includes ADC?
 * 25   Check the gpio pin connections & re-write them to reflect the new hardware
 *      IF_OUT_DIGITAL - Used for frequency counting - it's the raw signal digitised, GPIO 4
 *              No gain control on this pin.
 *      IF_OUT_PGA - Digital output, but amplified
 *      IF_OUT_TO_PI - for movement detection, post gain control
 *
 * 26   Check the filter code to use, high or notches
 *          Take this out for the Pi. Is there an alternative out there?
 * 27   On linkedLists, add a maximum number of readings to store & when exceeded, remove the tail. **URGENT
 *  DONE    2   Create a single H file for all the common stuff
 *  DONE            a What is the right way of doing this, is there a structure or a method for this?
 *  DONE            b What should I do about the various return status'
 *                  Should these be different value ranges
 *  CM 22  Updated linked lists to add a delete function
 *  24  Change gainFunctions to use typedef struct ...
 *          See the gainfunctions.h file
 *          i Split gainFunctions into user functions and internal functions
 *  7   Integrate LEDs into common library
 *          Not required at this time, integrate into the application instead.
 *  9   Code tidy up
 *          a Update comments and check they are correct
 *          b Update function descriptions in h files to ensure they are correct
 *              LEDControl
 *          c Remove redundant code
 *  13  Write instructions on how to compile into application
 *  15  Write some instructions on how to use the application
 *  16  Add tick marks to the scale for gain setting
 *  18  When starting up, set the value of the mode to unknown and not the first radiobutton
 *  20  Add scale and associated code to set the reading speed
 *  21  On run timer trigger when capturing values (running = true)
 *  4   Convert SPi to use ioctl as this doesn't require elevated privileges
 *  28  Change the GUI to give control over refresh time and data collection time
 * 
 *      
 *  DONE    8   Make Gain control structure contain required allowable values and use these in scale
 *  DONE    3   On GUI remove the bits at the bottom as they are not needed
 *  DONE    1   Get gain setting to only allow values available from the device
 *  DONE    16  Link the Mode Info at the bottom to the mode selected
 *  DONE    17  Link the Gain Setting at the bottom of the screen to the gain selected
 *  FIXED    BUG: There is something wrong with the graphing / linked list as the values don't match. When I have multiple data values
 *      in the linked list, the quantity graphed DON'T include the ones that were captured before switching to graph mode
 *      Could it be to do with the LinkedList within the structure NOT being a pointer.
 *      It would appear that the first value captured in the data timer is then not printed on the graph. I would guess it
 *      could be something to do with how I initialise the nodes within linkedlist.
  * DONE 10  Implement the smoothing algorithm in the common code
 *          see filter.c and filter.h
 *          The code is very short, but it takes quite a lot of processing power to run!
 *              It’s probably clear to you, but just pass each measured level to the relevant 
 *              filter and after the appropriate delay (until it has enough samples) it will 
 *              return the filtered values. notch_filter_100 will (obviously!) filters out the 
 *              [harmonics] of the 50Hz interference.  The coefficients are dependent on the 
 *              clock frequency, which I believe is 16MHz, so will need adjusting if you use a 
 *              different clock frequency.
 * DONE  5   Both gain and ADC use SPI, but on different lines, so I need to change serial port to spi port
 * DONE         a How do I have different settings for the same port?
 * DONE         b If the gain setting is done within the code and doesn't return the port, it can open and close it
 * DONE         c In the ADC reading, it needs to return the port so it can be used when reading new values
 *  DONE    19  Integrate program with reading of values as required by radiobutton setting
 *  DONE    a Firstly get random value to add in
 *  NOT REQD        a2 Change to using time and value
 *  NOT REQD           It will also need 2 data values, not 1
 *  NOT REQD    Not sure this is needed as values are captured in threads and therefore at a fixed time.
 *  DONE        This may need more linkedList functions / values
 *  DONE            max data value
 *  DONE            min data value
 *  DONE            quantity of readings
 *  DONE    a3 Change to use a scale values
 *  DONE        Need to move translate_example2 into radarVisual to get it drawing lines!
 *  DONE    a4 Change to have fixed max (3V3) and min values (0V)
 *  DONE    b Change to default source
 *  DONE    c Change to required source
 *  DONE        c2 Implement other sources
 *  DONE        Raw
 *  DONE        Filtered - see 10 below
 *  DONE        Frequency via digital
 * DONE 23  Update linked lists to include a counter and a maximum number of values
 * DONE     Counter added
 * DONE     a update structure to have the 2 variables, max reading, min reading
 * DONE 6   Rewrite common to be a better library
 * DONE         a Return success status
 * DONE         gainFunctions
 * DONE         rdr_spi_comms
 * DONE         gpioFunctions
 * DONE         rdr_gpio_control
 * DONE         adcFunctions
 * N/A          filter
 * DONE         ledControl
 * N/A          rdr_utilities
 * DONE         b Passing parameters into methods
 * DONE         c Receiving data from methods
 * DONE         e filenames - rdr_ for internal functions
 * DONE         f versioning
 * DONE         g ports for communications
 * DONE         h header file commenting format
 * DONE         j gpioFunctions needs to return values by parameter, not function name
 * DONE 17  Link gain setting to actually setting the gain value
 * DONE  12  Check which VCC the gain chip is operating at and set the GAIN_VCC accordingly
 * DONE  14  Write a licence header for all files and update them accordingly - emailed DB
 * DONE 11  Update existing programs with changes above
 * DONE         ** Some of them need to be removed as no longer required **
 * DONE         a readingAnalogueSignals
 * DONE         b gainControl
 * DONE             i This needs to have the menu in it, not the common
 * DONE         c mainTestProgram
 * DONE         d mainSampleSoftware
 * DONE         e readingDigitalSignals
 * DONE 29   Need to incorporate Start / Stop functionality
 * DONE         a Add in bus setup and closure into it
 * DONE         b Add in data running on or off
 * DONE         c Add in screen data refresh runing or not
 * 
 * 
 */


int open_serial_port( struct app_widgets *widget) {
    
	int		status = 1;
    // Open the serial port
    
    //status = setupComms(&widget->conn);
	printf("Opened the serial port:%d\n", widget->SPiconn);
    
    return status;
}

/*
 * Functions called by GUI
 */

// called when window is closed
void on_main_application_window_destroy() {
    printf("In on window main destroy\n");
    gtk_main_quit();
    
    exit(0);
}

void on_menu_file_connect(struct app_widgets *widget) {
    printf("In On Menu File connect\n");
    
	open_serial_port(widget);
    //get_version_info(widget);
	//get_mode_info(widget);
}

void on_btn_startstop_clicked(GtkButton *button, struct app_widgets *widget) {
	
	//int			status;
    int         reply;
    printf("Start / Stop button has been clicked\n");
    
    widget->running = !widget->running;
    
    if (widget->running) {
        printf("Currently Running\n");
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_raw))) {
            reply = adcSPiInitialisation();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
            reply = adcSPiInitialisation();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
            reply = setupGpioFunctions();
            if (reply == GPIO_EXIT_SUCCESS) {
                reply = setSampleHoldForRun();
            }
        }

    }
    else {
        printf("Currently NOT running\n");	
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_raw))) {
            adcSPiEnd();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
            adcSPiEnd();
        };

	return;
}

void on_btn_set_gain_clicked(GtkButton *button, struct app_widgets *widget) {
	
    char            conv[15];               // location for temporary conversion
    int             i = 0;
    
    //ToDo: Convert this so it uses the list from gainFunctions.c
    int             allowed_values[] = {0.2,1,10,20,30,40,60,80,120,157};
    int             allowed_values_size = sizeof(allowed_values)/sizeof(allowed_values[0]);
    int             set_value = 0;
    CommsRetCode    status = 0;

    printf("Set Gain button has been clicked\n");
    
    widget->gain_value = gtk_range_get_value(GTK_RANGE(widget->w_scale_gainctrl));
    printf("Gain Value Set:%d\n", widget->gain_value);
    
    // Need to get the value and determine where it actually is in the allowed values
    // and then write it back.
    
    printf("Size of array:%d\n", allowed_values_size);
    
    // Iterate through the list checking if the gain_value is greater than value given    
    i = 0;
    while(allowed_values[i] < widget->gain_value) {
        i++;

        if (i == (allowed_values_size)) {
            break;
        }
    };
    
    printf("Identified Entry:%d Posn:%d\n", allowed_values[i], i);
    
    // Got the upper position, now check what value to set_value to
    if (i == 0) {
        // the value selected is smaller than the lowest value in the list
        set_value = allowed_values[0];
    }
    else if (i == allowed_values_size) {
        // Reached the end of the list, set it to the max value
        set_value = allowed_values[i-1];
    }
    else {
        // Find the value between 2 limits
        if ((widget->gain_value - allowed_values[i-1]) < (allowed_values[i] - widget->gain_value)) {
            set_value = allowed_values[i-1];
        }
        else {
            set_value = allowed_values[i];
        }
    }

    gtk_range_set_value(GTK_RANGE(widget->w_scale_gainctrl), set_value);
    // set values of slider and gain setting box.
    
    sprintf(conv, "%d", set_value);
    printf("Converted:%s\n", conv);
    
    gtk_entry_set_text(GTK_ENTRY(widget->w_txt_gain_setting), conv);
    printf("set the text\n");

    //Write the new gain setting to the board    
    status = gainSPiInitialisation ();
    if (status != SPI_ERR_NONE) {
        status = setGa488inControl(set_value);
        if (status != SPI_ERR_NONE) {
            status = gainSPiEnd();
        }
    };

	
	return;
}

void on_radiobutton_toggled(GtkButton *button, struct app_widgets *widget) {
    
	char			mode;
    char            mode_full[15] = {'\0'};
    //GtkTextBuffer	*buffer;
	mode = '\0';
    
    printf("Radiobuttons for mode has changed\n");
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_raw))) {
        printf("Raw mode selected\n");
		mode = 'R';
        strcpy(mode_full, "ADC Raw");
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
        printf("Digital mode selected\n");
		mode = 'D';
        strcpy(mode_full, "Digital");
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
        printf("ADC mode selected\n");
		mode = 'A';
        strcpy(mode_full, "ADC Smoothed");
    }
    else {
        printf("Error occurred unknown mode selected\n");
        mode = '\0';
        strcpy(mode_full, "Unknown");
    }
    
    printf("Selected Mode:%c\n", mode);
    
    gtk_entry_set_text(GTK_ENTRY(widget->w_txt_mode_info), mode_full);
    printf("set the text\n");
    
    return;
}

gfloat f (gfloat x)
{
    // to the power calculation x to the power of y
    return 0.03 * pow (x, 3);
}

void on_draw (GtkWidget *drawing, cairo_t *cr, struct app_widgets *widget) {
	//Info: cr is passed as an extra parameter which is set in the glade file as user data.
    
    int count = 0;
    double x_scale, y_scale;

    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 5.0, dy = 5.0; /* Pixels between each point */
    gdouble clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
    gdouble left_margin = 5.0, bottom_margin = 5.0;         /* gap between edge and lines, percentage */

    Node *current;          // USed by the linked lists.

	
	GdkWindow *window = gtk_widget_get_window(drawing);	// I Think this needs to be the drawing canvas
	
    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window,
            &da.x,
            &da.y,
            &da.width,
            &da.height);

	printf("Got window geometry\n");
    printf("X coord:%d ", da.x);
    printf("Y coord:%d ", da.y);
    printf("Width  :%d ", da.width);
    printf("Height :%d\n", da.height);
    // X coord:5 Y coord:5 Width  :500 Height :307
	
	/* Draw on a black background */
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_paint (cr);
	printf("drawn on black background\n");

    // Set how the devie to usder layer translate - keeping it the same.
    cairo_translate (cr, 0, 0);
    
    // Move zero points:cairo_scale (cr, ZOOM_X, -ZOOM_Y);
	//cairo_scale (cr, 95, 95);
	cairo_scale (cr, (da.width/100), (da.height/100));
	printf("changed the transformation matrix\n");
	
    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    
	
    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    // horizontal axis
    cairo_move_to (cr, clip_x1+left_margin, clip_y2-bottom_margin);
    cairo_line_to (cr, clip_x2, clip_y2-bottom_margin);
    // vertical axis
    cairo_move_to (cr, clip_x1+left_margin, clip_y1);
    cairo_line_to (cr, clip_x1+left_margin, clip_y2-bottom_margin);
    cairo_stroke (cr);
	printf("drawn x and y axis\n");

    // No values to draw, so just return at this point.
    if (widget->list.qty_readings == 0) {
        //Noting to draw
        printf("Nothing to draw\n");
        return;
    }
    
    // Calculate the x and y scale
    /*  X Scale is determined by the drawing scale divided by the quantity of readings
        The Y scale is determined by the quantity of readings divided by max minus min*/
    x_scale = ((clip_x2 - clip_x1 - left_margin) / widget->list.qty_readings);
    // The one below sets the scale based on max and min readings.
    y_scale = ((clip_y2 - clip_x1 - bottom_margin) / (widget->list.max_reading - widget->list.min_reading));
    
    // There was a thought to use a fixed scale of 0 to 3v3, but in one mode it reads frequency, and therefore this isn't any use
    //y_scale = ((clip_y2 - clip_x1 - bottom_margin) / MAX_VOLTAGE);      // Y Scale is 0 to 3V3 fixed.
    
    cairo_set_line_width (cr, dx);
	printf("Determined the data points\n");
    printf("dx:%lf dy:%lf\n", dx, dy);
    printf("clip_x1:%lf ", clip_x1);
    printf("clip_x2:%lf ", clip_x2);
    printf("clip_y1:%lf ", clip_y1);
    printf("clip_y2:%lf\n", clip_y2);
    printf("qty readings:%d ", widget->list.qty_readings);
    printf("max reading:%f ", widget->list.max_reading);
    printf("min reading:%f ", widget->list.min_reading);
    printf("X scale:%lf ", x_scale);
    printf("Y scale:%lf\n", y_scale);


    current = widget->list.listHead;
    cairo_line_to(cr, 50, 50);
    // Draw the graph
    // Move to the first reading, before cycling through
    //                  move to the left + margin
    //                                        move to the bottom, up the margin (0,0 is at the top)
    //                                                                    move up to the reading
    cairo_move_to (cr, (clip_x1+left_margin), (clip_y2 - bottom_margin) - ((current->reading - widget->list.min_reading) * y_scale));

    do {
        //                  move across a step in x scale plus the margin
        //                                                 starting from the bottom, less the margin
        //                                                                            move up the reading in y scale
        cairo_line_to (cr, (count * x_scale)+left_margin, (clip_y2 - bottom_margin) - ((current->reading - widget->list.min_reading) * y_scale));      //Draws a line from the current position, to the new coordinates

        printf("Reading:%d  Data:%f\n", count, current->reading);
        current = current->nextnode;
        count ++;
    } while (count < widget->list.qty_readings);
	
	printf("Linked data points\n");
	
    /* Draw the curve */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);
	printf("Drawn the curve\n");
    return;
}

gboolean screen_timer_exe(struct app_widgets *widget) {
    printf("In screen refresh timer trigger\n");
    
    if (widget->running != true) {
        // It is currently not running, therefore don't refresh the screen.
        return true;
    }

     
    // triggers the redraw of the window
    gtk_widget_queue_draw (widget->w_canvas_graph);
    
    // The function must return TRUE to trigger the next instance
    // If it returns false, it stops.
    return true;
}

gboolean data_timer_exe(struct app_widgets *widget) {
    printf("In data timer\n");
    
    //ToDo: Implement linked lists here...
    /* Version 1: Get some random data and put it into a linked list*/
    int reply = 0;              // the reply status from the code
    float   reading = 0.0;
    
    if (widget->running != true) {
        // It is currently not running, therefore don't capture any values.
        if (widget->list->listHead != NULL) {
            // List is initialised and needs to be cleared ahead of the a new list running.
            listInitialise(&widget->list);
        }
        return true;
    }
    //Get some data
    
    // Random number generation
    //int value = 0;
    //value = (rand() % 300);
    //// Add a new value to the start of the list every time it runs
    //listAddHead(&widget->list, value);

    /* Need to set maximum & minimum values here as part of mode because the digital mode
     * returns frequency, not voltage
     * So I need to add functions to set max and set min and allow draw to use max and min.
     */
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_raw))) {

        printf("Raw data mode selected\n");
        if (reply == ADC_EXIT_SUCCESS) {
            reply = readVoltage(&reading);
        }
        // In this mode, max and min are based on the voltage output of the adc, hence set to max and min here
        listSetMax(&widget->list, MAX_VOLTAGE);
        listSetMin(&widget->list, MIN_VOLTAGE);
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
        printf("ADC data mode selected\n");
        // Add filter here with ADC
        if (reply == ADC_EXIT_SUCCESS) {
            reply = readVoltage(&reading);
            reading = highpass_filter (reading);
        }
        // In this mode, max and min are based on the voltage output of the adc, hence set to max and min here
        listSetMax(&widget->list, MAX_VOLTAGE);
        listSetMin(&widget->list, MIN_VOLTAGE);
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
        printf("Digital data mode selected\n");
        if (reply == GPIO_EXIT_SUCCESS) {
            reply = returnFullFrequency(&reading, IF_OUT_TO_PI);
        }
    };

    printf("Voltage read:%f\n", reading);
    //// Add a new value to the start of the list every time it runs
    listAddHead(&widget->list, reading);
    
    return true;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    GtkBuilder      *builder; 
    GtkWidget       *window;
    
    GError                  *err = NULL;    // holds any error that occurs within GTK
    
    // instantiate structure, allocating memory for it
    struct app_widgets	*widgets = g_slice_new(struct app_widgets);
    
    listInitialise(&widgets->list);
    init_filter();
    
    // initialise GTK library and pass it in command line parameters
    gtk_init(&argc, &argv);

    // build the gui
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "../Visual/gui/main_window.glade", &err);
	
	//Bug: If the application is NOT run from the build directory, it doesn't find the glade file.
	//		 Does this mean that the XML file is not incorporated into the executable??
    
    // check if the GUI has opened.
    if (err != NULL) {
		fprintf (stderr, "Unable to read file: %s\n", err->message);
		g_error_free(err);
		return 1;
    }
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_application_window"));
    
    // build the structure of widget pointers
    widgets->w_radbut_adc       = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_adc"));
    widgets->w_radbut_digital   = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_digital"));
    widgets->w_radbut_raw       = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_raw"));
    widgets->w_scale_gainctrl   = GTK_WIDGET(gtk_builder_get_object(builder, "scale_gainctrl"));
    widgets->w_btn_set_gain     = GTK_WIDGET(gtk_builder_get_object(builder, "btn_set_gain"));
    widgets->w_canvas_graph     = GTK_WIDGET(gtk_builder_get_object(builder, "canvas_graph"));
    widgets->w_btn_startstop    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_startstop"));
    widgets->w_txt_mode_info    = GTK_WIDGET(gtk_builder_get_object(builder, "txt_mode_info"));
    widgets->w_txt_gain_setting = GTK_WIDGET(gtk_builder_get_object(builder, "txt_gain_setting"));
    widgets->w_adj_gainctrl     = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adj_gainctrl"));
    
    
    // connect the widgets to the signal handler
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);
    
	// ToDo: need to get this to try and if fail, report to the user. Maybe have it only run by the menu item rather than automatic.
    on_menu_file_connect(widgets);

    // Set the variables to their initial state
    widgets->running = false;                       // Not running initially

    
    // Set a timeout running to refresh the screen
    gdk_threads_add_timeout(SCREEN_REFRESH_TIMER, (GSourceFunc)screen_timer_exe, (gpointer)widgets);
    gdk_threads_add_timeout(DATA_REFRESH_TIMER, (GSourceFunc)data_timer_exe, (gpointer)widgets);


    
    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(struct app_widgets, widgets);
    
    return (EXIT_SUCCESS);
}
