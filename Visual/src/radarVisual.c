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

#include <gtk-3.0/gtk/gtk.h>
#include <math.h>
#include <cairo.h>

#include "../inc/radarVisual.h"


// Copied from elsewhere, need to modify it to test the frame.
#define WIDTH   640
#define HEIGHT  480

#define ZOOM_X  100.0
#define ZOOM_Y  100.0

gfloat f (gfloat x)
{
    return 0.03 * pow (x, 3);
}

void on_draw (GtkWidget *drawing, cairo_t *cr, struct app_widgets *widget) {
	//Info: cr is passed as an extra parameter which is set in the glade file as user data.
	// Need to check this is right before I conclude I know what I am doing

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
	
	/* Draw on a black background */
    cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
    cairo_paint (cr);
	printf("drawn on black background\n");

    /* Change the transformation matrix */
    cairo_translate (cr, da.width / 2, da.height / 2);
    cairo_scale (cr, ZOOM_X, -ZOOM_Y);
	printf("changed the transformation matrix");
	
    /* Determine the data points to calculate (ie. those in the clipping zone */
    cairo_device_to_user_distance (cr, &dx, &dy);
    cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
    cairo_set_line_width (cr, dx);
	printf("Determined the data points\n");
	
    /* Draws x and y axis */
    cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
    cairo_move_to (cr, clip_x1, 0.0);
    cairo_line_to (cr, clip_x2, 0.0);
    cairo_move_to (cr, 0.0, clip_y1);
    cairo_line_to (cr, 0.0, clip_y2);
    cairo_stroke (cr);
	printf("drawn x and y axis\n");
	
    /* Link each data point */
	for (i = clip_x1; i < clip_x2; i += dx)
		cairo_line_to (cr, i, f (i));
	
	printf("Linked data points\n");
	
    /* Draw the curve */
    cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
    cairo_stroke (cr);
	printf("Drawn teh curve\n");

    return;
}



/*
 * function to open and configure the serial port
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

void on_btn_startstop_adc_clicked(GtkButton *button, struct app_widgets *widget) {
	
	//int			status;
    printf("ADC button has been clicked\n");
	
	//on_draw(widget->w_adc_drg_canvas);		//How do i trigger starting of the drawing?
	return;
}

void on_btn_startstop_dig_clicked(GtkButton *button, struct app_widgets *widget) {
	
	//int			status;
    printf("Dig button has been clicked\n");
	
	return;
}

void on_btn_startstop_raw_clicked(GtkButton *button, struct app_widgets *widget) {
	
	//int			status;
    printf("Raw button has been clicked\n");
	
	return;
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
	
	//Bug: If the application is run from the build directory, it doesn't find the glade file.
	//		 Does this mean that the XML file is not incorporated into the executable??
    
    // check if the GUI has opened.
    if (err != NULL) {
		fprintf (stderr, "Unable to read file: %s\n", err->message);
		g_error_free(err);
		return 1;
    }
    
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_application_window"));
    
    // build the structure of widget pointers
    widgets->w_adc_drg_canvas  = GTK_WIDGET(gtk_builder_get_object(builder, "adc_drg_canvas"));
    widgets->w_dig_drg_canvas  = GTK_WIDGET(gtk_builder_get_object(builder, "dig_drg_canvas"));
    widgets->w_raw_drg_canvas  = GTK_WIDGET(gtk_builder_get_object(builder, "raw_drg_canvas"));
    widgets->w_but_startstop_adc1  = GTK_WIDGET(gtk_builder_get_object(builder, "but_startstop_adc1"));
    widgets->w_but_startstop_dig  = GTK_WIDGET(gtk_builder_get_object(builder, "but_startstop_dig"));
    widgets->w_but_startstop_raw  = GTK_WIDGET(gtk_builder_get_object(builder, "but_startstop_raw"));
    
    // connect the widgets to the signal handler
    gtk_builder_connect_signals(builder, widgets);    // note: second parameter points to widgets
    g_object_unref(builder);
    
    // Set the status of the various boxes etc.
	//ToDo: need to set the txt_version_info box to not editable.
    //gtk_text_view_set_editable(GtkTextView (widgets->w_txt_version_info_box), FALSE);
    
	// ToDo: need to get this to try and if fail, report to the user. Maybe have it only run by the menu item rather than automatic.
    on_menu_file_connect(widgets);

    
    gtk_widget_show(window);                
    gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits
    g_slice_free(struct app_widgets, widgets);
    
    return (EXIT_SUCCESS);
}
