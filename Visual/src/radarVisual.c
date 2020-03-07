/* 
 * File:   radarVisual.c
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 30 March 2019, 09:34
 * 
 * Example code for providing a full GUI interface to read and configure
 * the Radar PI
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
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


/*
 * Functions called by GUI
 */

// called when window is closed
void on_main_application_window_destroy() {
    printf("In on window main destroy\n");
    gtk_main_quit();
    
    exit(0);
}

void on_btn_startstop_clicked(GtkButton *button, struct app_widgets *widget) {
	
	//int			status;
    int         reply;
    printf("Start / Stop button has been clicked\n");
    
    widget->running = !widget->running;
    
    if (widget->running) {
        printf("Currently Running\n");
        gtk_entry_set_text(GTK_ENTRY(widget->w_txt_status), "Running");
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_op_to_pi))) {
            reply = adcSPiInitialisation();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
            reply = adcSPiInitialisation();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
            // nothing required.
        }
    }
    else {
        printf("Currently NOT running\n");	
        gtk_entry_set_text(GTK_ENTRY(widget->w_txt_status), "Not Running");
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_op_to_pi))) {
            adcSPiEnd();
        }
        else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
            adcSPiEnd();
        };
    }
	return;
}

void on_btn_config_clicked(GtkButton *button, struct app_widgets *widget){
    
    widget->running = false;
    gtk_entry_set_text(GTK_ENTRY(widget->w_txt_status), "Not Running");
    return;
}

int set_gain(GtkButton *button, struct app_widgets *widget) {
	
    char            conv[15];               // location for temporary conversion
    int             i = 0;
    
    //ToDo: Convert this so it uses the list from gainFunctions.c
    double          allowed_values[] = {0.2,1,10,20,30,40,60,80,120,157};
    int             gain_values[] = {0b1001, 0b0000, 0b0001, 0b0010, 0b0011, 0b0100, 0b0101, 0b0110, 0b0111, 0b1000};
    int             allowed_values_size = sizeof(allowed_values)/sizeof(allowed_values[0]);
    CommsRetCode    status = 0;

    widget->gain_value = gtk_range_get_value(GTK_RANGE(widget->w_scale_gainctrl));
    if (DEBUG1 <= widget->debug) {
        printf("Gain Value Set:%d\n", widget->gain_value);
    }
    
    // Need to get the value and determine where it actually is in the allowed values
    // and then write it back.
    
    // Iterate through the list checking if the gain_value is greater than value given    
    i = 0;
    while(allowed_values[i] < widget->gain_value) {
        i++;
        if (i == allowed_values_size) {
            // Reached the end of the list of values and not found
            break;
        }
    };
    
    if (DEBUG1 <= widget->debug) {
        printf("Identified Entry:%0.1f Posn:%d\n", allowed_values[i], i);
    }

    // set values of slider and gain setting box.
    
    sprintf(conv, "%0.1f", allowed_values[i]);
    if (DEBUG1 <= widget->debug) {
        printf("Converted:%s\n", conv);
    }

    //Write the new gain setting to the board    
    status = gainSPiInitialisation ();
    if (status == SPI_ERR_NONE) {
        status = setGainControl(gain_values[i]);
        
        if (status == SPI_ERR_NONE) {
            // Gain has been set, now end comms and set the boxes / slider
            gainSPiEnd();
            gtk_entry_set_text(GTK_ENTRY(widget->w_txt_gain_setting), conv);
            gtk_range_set_value(GTK_RANGE(widget->w_scale_gainctrl), allowed_values[i]);
            if (DEBUG1 <= widget->debug) {
                printf("Set Gain Comms ended\n");
            }
        } else {
            if (DEBUG2 <= widget->debug) {
                printf("Unable to set Gain Control, error code:%d\n", status);
            }
        };
    }
    else {
        if (DEBUG2 <= widget->debug) {
            printf("Unable to start SPI Comms, error code:%d", status);
        }
    };
    if (status !=SPI_ERR_NONE) {
        gtk_entry_set_text(GTK_ENTRY(widget->w_txt_gain_setting), "Error");
        gtk_range_set_value(GTK_RANGE(widget->w_scale_gainctrl), 0);
        if (DEBUG1 <= widget->debug) {
            printf("Gain Set - i think\n");
        }
    }

	return status;
}

void on_btn_set_clicked(GtkButton *button, struct app_widgets *widget) {

    int     status;
    char    mode_full[15] = {'\0'};

    // Set the gain from the slider
    status = set_gain(button, widget);
    
    if (status != SPI_ERR_NONE) {
        printf("Failed to set gain\n");
        //ToDo: Reset back to pre change. - Use on_btn_ignore clicked
    }
    
    // Set the info box Mode    
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_op_to_pi))) {
        strcpy(mode_full, "Output to Pi");
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
        strcpy(mode_full, "Digital");
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
        strcpy(mode_full, "ADC Smoothed");
    }
    else {
        printf("Error occurred unknown mode selected\n");
        strcpy(mode_full, "Unknown");
    }
    gtk_entry_set_text(GTK_ENTRY(widget->w_txt_mode_info), mode_full);
    printf("set the mode\n");
    
    gtk_label_set_text(GTK_LABEL(widget->w_lbl_user_message), "");
    
    return;
    
}

void on_btn_ignore_clicked(GtkButton *button, struct app_widgets *widget) {

    // Set the gain back to the old value
    printf("Not yet implemented\n");
    
    
    // Set the info boxes
    //      Mode
    //      Gain
    
    return;
}

void old_on_btn_set_gain_clicked(GtkButton *button, struct app_widgets *widget) {
	
    char            conv[15];               // location for temporary conversion
    int             i = 0;
    
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
        status = setGainControl(set_value);
        if (status != SPI_ERR_NONE) {
            status = gainSPiEnd();
        }
    };

	
	return;
}

void old_on_radiobutton_toggled(GtkButton *button, struct app_widgets *widget) {
    
	char			mode;
    char            mode_full[15] = {'\0'};
    //GtkTextBuffer	*buffer;
	mode = '\0';
    
    printf("Radiobuttons for mode has changed\n");
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_op_to_pi))) {
        printf("O/P to Pi mode selected\n");
		mode = 'R';
        strcpy(mode_full, "O/P to Pi");
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
    gdouble axis_width = 1.0, line_width = 1.0; /* Pixels between each point */
    
    Node *current;          // Used by the linked lists.

	
	GdkWindow *window = gtk_widget_get_window(drawing);	// I Think this needs to be the drawing canvas
	
    /* Determine GtkDrawingArea dimensions */
    gdk_window_get_geometry (window,
            &da.x,
            &da.y,
            &da.width,
            &da.height);

    if (DEBUG1 <= widget->debug) {  //Debug comments
        printf("Got window geometry\n");
        printf("X coord:%d ", da.x);
        printf("Y coord:%d ", da.y);
        printf("Width  :%d ", da.width);
        printf("Height :%d\n", da.height);
        // X coord:5 Y coord:5 Width  :500 Height :307
	};
    
	/* Draw on a black background */
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_paint (cr);

    // Set how the device to usder layer translate - keeping it the same.
    cairo_translate (cr, 0, 0);
    
    // Move zero points:cairo_scale (cr, ZOOM_X, -ZOOM_Y);
	//cairo_scale (cr, 95, 95);
	cairo_scale (cr, (da.width/100), (da.height/100));
	//printf("changed the transformation matrix\n");        //Debug comment
	
    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    
	
    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    cairo_set_line_width (cr, axis_width);
    // horizontal axis
    cairo_move_to (cr, clip_x1+left_margin, clip_y2-bottom_margin);
    cairo_line_to (cr, clip_x2, clip_y2-bottom_margin);
    // vertical axis
    cairo_move_to (cr, clip_x1+left_margin, clip_y1);
    cairo_line_to (cr, clip_x1+left_margin, clip_y2-bottom_margin);
    cairo_stroke (cr);

    // No values to draw, so just return at this point.
    if (widget->list.qty_readings == 0) {
        //Noting to draw
        if (DEBUG1 <= widget->debug) {
            printf("Nothing to draw\n");
        }
        return;
    }
    
    // Calculate the x and y scale
    /*  X Scale is determined by the drawing scale divided by the quantity of readings
        The Y scale is determined by the quantity of readings divided by max minus min*/
    x_scale = ((clip_x2 - clip_x1 - left_margin) / widget->list.qty_readings);
    // The one below sets the scale based on max and min readings.
    y_scale = ((clip_y2 - clip_x1 - bottom_margin) / (widget->list.max_reading - widget->list.min_reading));
    
    cairo_set_line_width (cr, line_width);
    //Debug comments
    if (DEBUG1 <= widget->debug) {
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
    }

    current = widget->list.listHead;
    cairo_line_to(cr, 50, 50);
    // Draw the graph
    // Move to the first reading, before cycling through
    //                  move to the left + margin
    //                                        move to the bottom, up the margin (0,0 is at the top)
    //                                                                    move up to the reading
    cairo_move_to (cr, (clip_x1+left_margin), (clip_y2 - bottom_margin) - ((current->reading - widget->list.min_reading) * y_scale));

    printf("Latest 5 readings ONLY\n");        // Debug comment

    do {
        //                  move across a step in x scale plus the margin
        //                                                 starting from the bottom, less the margin
        //                                                                            move up the reading in y scale
        cairo_line_to (cr, (count * x_scale)+left_margin, (clip_y2 - bottom_margin) - ((current->reading - widget->list.min_reading) * y_scale));      //Draws a line from the current position, to the new coordinates

        // Debug messaging, print 5 newest readings only
        if (count < 5) {
            printf("Reading:%d  Data:%f\n", count, current->reading);
        }
        current = current->nextnode;
        count ++;
    } while (count < widget->list.qty_readings);
	
	//printf("Linked data points\n");        //Debug comment
	
    /* Draw the curve */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);
	printf("Drawn the curve\n");
    return;
}

gboolean screen_timer_exe(struct app_widgets *widget) {
    if (DEBUG1 <= widget->debug) {
        printf("In screen refresh timer trigger\n");
    }
    
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
    if (DEBUG1 <= widget->debug) {
        printf("In data timer\n");
    }
    
    int reply = 0;              // the reply status from the code
    float   reading = 0.0;
    
    if (widget->running != true) {
        // It is currently not running, therefore don't capture any values.
        if (widget->list.listHead != NULL) {
            // List is initialised and needs to be cleared ahead of the a new list running.
            listInitialise(&widget->list);
        }
        return true;
    }
    //Get some data
    
    // Random number generation
    //printf("random number generator\n");
    //reading = (rand() % 300);
    // Add a new value to the start of the list every time it runs
    //listAddHead(&widget->list, reading);
    //return true;

    /* Need to set maximum & minimum values here as part of mode because the digital mode
     * returns frequency, not voltage
     * So I need to add functions to set max and set min and allow draw to use max and min.
     */
    
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_adc))) {
        if (DEBUG1 <= widget->debug) {
            printf("ADC data mode selected\n");
        }
        // Add filter here with ADC
        if (reply == ADC_EXIT_SUCCESS) {
            reply = readVoltage(&reading);
            //reading = highpass_filter (reading);
        }
        // In this mode, max and min are based on the voltage output of the adc, hence set to max and min here
        listSetMax(&widget->list, MAX_VOLTAGE);
        listSetMin(&widget->list, MIN_VOLTAGE);
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_op_to_pi))) {
        if (DEBUG1 <= widget->debug) {
            printf("O/P to PI mode selected\n");
        }
        if (reply == ADC_EXIT_SUCCESS) {
            reply = returnFullFrequency(&reading, IF_OUT_DIGITAL);
        }
    }
    else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget->w_radbut_digital))) {
        if (DEBUG1 <= widget->debug) {
            printf("Digital data mode selected\n");
        }
        if (reply == GPIO_EXIT_SUCCESS) {
            reply = returnFullFrequency(&reading, IF_OUT_DIGITAL);
        }
    };

    if (DEBUG1 <= widget->debug) {
        printf("Voltage read:%f\n", reading);
    }
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
    int             status;
    int             arg_count;
    
    GError                  *err = NULL;    // holds any error that occurs within GTK
    
    // instantiate structure, allocating memory for it
    struct app_widgets	*widgets = g_slice_new(struct app_widgets);
    
    // Handle main program arguments
    // Format radarVisual DEBUG x       where x is the level 0 - 4, if omitted, level = 1
    if (argc > 1) {
        for(arg_count=0;arg_count<argc;arg_count++) {
            printf("\nargv[%d]: %s\n",arg_count,argv[arg_count]);
        }
        // Looking for argument 1 and it's not there!!
        if (strcmp(argv[1],"DEBUG") == 0) {      //argv is 'DEBUG'
            // atoi will either return a number or zero if it can't convert it
            // Therefore set the debug to the number
            if (argc >= 3) {
                widgets->debug = atoi(argv[2]);
            }
            else {
                widgets->debug = 1;
            }
        }
    }
    else {
        widgets->debug = false;
    };
    
    if (DEBUG1 <= widgets->debug) {
        printf("Debug level: %d\n", widgets->debug);
    }
    
    listInitialise(&widgets->list);
    init_filter();
    
    status = setupGpioFunctions();
    if (status == GPIO_EXIT_SUCCESS) {
        status = setSampleHoldForRun();
        printf("Sample & Hold set to Run\n");
    }
    if (status != GPIO_EXIT_SUCCESS) {
        printf("Unable to setup GPIO, please check and re-run\n");
        return status;
    }

    
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
    widgets->w_radbut_adc           = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_adc"));
    widgets->w_radbut_digital       = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_digital"));
    widgets->w_radbut_op_to_pi      = GTK_WIDGET(gtk_builder_get_object(builder, "radbut_op_to_pi"));
    widgets->w_scale_gainctrl       = GTK_WIDGET(gtk_builder_get_object(builder, "scale_gainctrl"));
    widgets->w_btn_set_gain         = GTK_WIDGET(gtk_builder_get_object(builder, "btn_set_gain"));
    widgets->w_canvas_graph         = GTK_WIDGET(gtk_builder_get_object(builder, "canvas_graph"));
    widgets->w_btn_startstop        = GTK_WIDGET(gtk_builder_get_object(builder, "btn_startstop"));
    widgets->w_txt_mode_info        = GTK_WIDGET(gtk_builder_get_object(builder, "txt_mode_info"));
    widgets->w_txt_gain_setting     = GTK_WIDGET(gtk_builder_get_object(builder, "txt_gain_setting"));
    widgets->w_adj_gainctrl         = GTK_ADJUSTMENT(gtk_builder_get_object(builder, "adj_gainctrl"));
    widgets->w_txt_status           = GTK_WIDGET(gtk_builder_get_object(builder, "txt_status"));
    widgets->w_lbl_user_message     = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_user_message"));
    
    
    // connect the widgets to the signal handler
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);

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
