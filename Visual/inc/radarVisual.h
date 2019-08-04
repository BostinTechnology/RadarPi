/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidVisual.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:14
 */

#ifndef RFIDVISUAL_H
#define RFIDVISUAL_H

struct app_widgets {
    // All the widgets on the form go into here
    GtkWidget *w_adc_drg_canvas;
    GtkWidget *w_dig_drg_canvas;    
    GtkWidget *w_raw_drg_canvas;
    GtkWidget *w_but_startstop_adc1;
    GtkWidget *w_but_startstop_dig;
    GtkWidget *w_but_startstop_raw;
    // also the SPI connection
    int        SPiconn;
} ;


//ToDo: improve the commentary for the functions


int open_serial_port(struct app_widgets *widget);

// calls the library and gets the version info
void on_main_application_window_destroy() ;


#endif /* RFIDVISUAL_H */

