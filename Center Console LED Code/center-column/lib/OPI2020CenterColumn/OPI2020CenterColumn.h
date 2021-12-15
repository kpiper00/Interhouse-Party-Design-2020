/**
 * OPI2020CenterColumn.h
 * Main header for OPI 2020 Center Column library
 *
 * Description:
 *      This file is the main header file for the center column LED setup at 
 *      OPI 2020, built using one Bifrost RGB LED controller
 *
 * Author:          Ray Sun
 * Last Updated:    02/25/2020
 */
 
 
#ifndef OPI2020CC_H
#define OPI2020CC_H


#include <Heimdall.h>


#define     N_LEDS      60          // Number of LEDs per strip

#define     N_STRIPS    6           // Number of strips in the center column

#define     OUT5_PIN    BTN2_PIN    // D3
#define     OUT6_PIN    BTN3_PIN    // D4


#endif // OPI2020CC_H