/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpio_control.h
 * Author: Matthew
 *
 * Created on 22 August 2018, 15:54
 */

#ifndef GPIO_CONTROL_HEADER
#define GPIO_CONTROL_HEADER

#define BLOCK_SIZE		(4*1024)

/* The range of GPIO pins available to use*/
#define LOWEST_GPIO_PIN					0			// Lowest acceptable GPIO pin
#define HIGHEST_GPIO_PIN				53			// Highest acceptable GPIO pin

/* Offset to the registers. The first register is zero, the rest are listed below
 * The offset is to the first register in a type, e.g. The PIn register for GPIO's 0 - 31
 * There is no offset for the first register as this starts at zero */
#define GPIO_SET_OFFSET					7			// GPSET0 Pin Output Set registers
#define GPIO_CLEAR_OFFSET				10			// GPCLR0 Pin Output Clear registers
#define GPIO_LEVEL_OFFSET				13			// GPLEV0 Pin Level register

#include <stdint.h>

// functions
int gpio_init();							// Initialise the gpio system
int set_gpio_for_input(int pin_no);			// Set a GPIO pin for input
int set_gpio_for_output(int pin_no);		// Set a GPIO pin for output
int set_gpio_value (int pin_no, int value);	// Set the value (0 or 1) of a GPIO pin
int read_gpio_value(int pin_no);			// Read a GPIO pin value


// Global Variables
static volatile uint32_t *gpio_mmap;                  // the mmap pointer for the gpio map


#endif


