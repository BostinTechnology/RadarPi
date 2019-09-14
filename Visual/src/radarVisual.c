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

#include <gtk-3.0/gtk/gtk.h>
#include <math.h>
#include <cairo.h>
#include <unistd.h>
#include <pthread.h>

#include "../inc/radarVisual.h"
#include "../../common/inc/radar.h"

/*******************************************************************************
 *
 *  To Do List
 *  ==========
 *
 *  DONE    2   Create a single H file for all the common stuff
 *              a What is the right way of doing this, is there a structure or a method for this?
 *  DONE    8   Make Gain control structure contain required allowable values and use these in scale
 *  DONE    3   On GUI remove the bits at the bottom as they are not needed
 *  DONE    1   Get gain setting to only allow values available from the device
 *  DONE    16  Link the Mode Info at the bottom to the mode selected
 *  DONE    17  Link the Gain Setting at the bottom of the screen to the gain selected
 *  19  Integrate program with reading of values as required by radiobutton setting
 *          a Firstly get random value to add in
 *          a2 Change to using time and value
 *              This may need more linkedList functions (max and min values)
 *              It will also need 2 data values, not 1
 *          b Change to default source
 *          c Change to required source
 *  CM 22  Updated linked lists to add a delete function
 *  CM 23  Update linked lists to include a counter and a maximum number of values
 *          a update structure to have the 2 variables
 *          b when exceeded, remove the tail.
 *  10  Implement the smoothing algorithm in the common code
 *          see filter.c and filter.h
 *          The code is very short, but it takes quite a lot of processing power to run!
 *              It’s probably clear to you, but just pass each measured level to the relevant 
 *              filter and after the appropriate delay (until it has enough samples) it will 
 *              return the filtered values. notch_filter_100 will (obviously!) filters out the 
 *              [harmonics] of the 50Hz interference.  The coefficients are dependent on the 
 *              clock frequency, which I believe is 16MHz, so will need adjusting if you use a 
 *              different clock frequency.
 *  24  Change gainFunctions to use typedef struct ...
 *          See the gainfunctions.h file
 *  5   Both gain and ADC use SPI, but on different lines, so I need to change serial port to spi port
 *          a How do I have different settings for the same port?
 *          b If the gain setting is done within the code and doesn't return the port, it can open and close it
 *          c In the ADC reading, it needs to return the port so it can be used when reading new values
 *  17  Link gain setting to actually setting the gain value
 *  6   Rewrite common to be a better library
 *          a Not sure what this looks like - emailed CM
 *  7   Integrate LEDs into common library
 *  9   Code tidy up
 *          a Update comments and check they are correct
 *          b Update function descriptions in h files to ensure they are correct
 *          c Remove redundant code
 *  11  Update existing programs with changes above
 *          ** Some of them need to be removed as no longer required **
 *          a readingAnalogueSignals
 *          b settingGainControl
 *              i This needs to have the menu in it, not the common
 *          c mainTestProgram
 *          d mainSampleSoftware
 *          e readingDigitalSignals
 *  12  Check which VCC the gain chip is operating at and set the GAIN_VCC accordingly
 *  13  Write instructions on how to compile into application
 *  14  Write a licence header for all files and update them accordingly - emailed DB
 *  15  Write some instructions on how to use the application
 *  16  Add tick marks to the scale
 *  18  When starting up, set the value of the mode to unknown and not the first radiobutton
 *  20  Add scale and associated code to set the reading speed
 *  21  On run timer trigger when capturing values (running = true)
 *  4   Convert SPi to use ioctl as this doesn't require elevated privileges
 *          No sure this is requried as program runs on

 * 
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
    printf("Start / Stop button has been clicked\n");
    
    widget->running = !widget->running;
    
    if (widget->running) {
        printf("Currently Running\n");
    }
    else {
        printf("Currently NOT running\n");
    }
	
	return;
}

void on_btn_set_gain_clicked(GtkButton *button, struct app_widgets *widget) {
	
    char            conv[15];               // location for temporary conversion
    int             i = 0;
    
    //ToDo: Convert this so it uses the list from gainFunctions.c
    int             allowed_values[] = {0.2,1,10,20,30,40,60,80,120,157};
    int             allowed_values_size = sizeof(allowed_values)/sizeof(allowed_values[0]);
    int             set_value = 0;

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
    
    //ToDo: Write the new gain setting to the board
	
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

    GdkRectangle da;            /* GtkDrawingArea size */
    gdouble dx = 5.0, dy = 5.0; /* Pixels between each point */
    gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
	
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

    /* Change the transformation matrix */
    cairo_translate (cr, da.width / 2, da.height / 2);
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);
	printf("changed the transformation matrix\n");
	
    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, dx);
	printf("Determined the data points\n");
    printf("dx:%lf dy:%lf\n", dx, dy);
    printf("clip_x1:%lf ", clip_x1);
    printf("clip_y1:%lf ", clip_y1);
    printf("clip_x2:%lf ", clip_x2);
    printf("clip_y2:%lf\n", clip_y2);
    //dx:0.050000 dy:-0.050000 
    //clip_x1:-2.500000 clip_y1:-1.540000 clip_x2:2.500000 clip_y2:1.530000

	
    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    cairo_move_to (cr, clip_x1, 0.0);
    cairo_line_to (cr, clip_x2, 0.0);
    cairo_move_to (cr, 0.0, clip_y1);
    cairo_line_to (cr, 0.0, clip_y2);
    cairo_stroke (cr);
	printf("drawn x and y axis\n");
	
    //ToDo: Implement linked lists here...
    /* Link each data point */
	for (i = clip_x1; i < clip_x2; i += dx)
		cairo_line_to (cr, i, f (i));       //Draws a line from the current position, to the new coordinates
	
	printf("Linked data points\n");
	
    /* Draw the curve */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);
	printf("Drawn the curve\n");
    return;
}

gboolean screen_timer_exe(struct app_widgets *widget) {
    printf("In screen refresh timer trigger\n");
     
    // triggers the redraw of the window
    gtk_widget_queue_draw (widget->w_canvas_graph);
    
    // The function must return TRUE to trigger the next instance
    // If it returns false, it stops.
    return true;
}

gboolean data_timer_exe(struct app_widgets *widget) {
    printf("In data timer\n");
    
    //Get some data
    
    /* Version 1: Get some random data and put it into a linked list*/
    
    //ToDo: Implement linked lists here...
    
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
