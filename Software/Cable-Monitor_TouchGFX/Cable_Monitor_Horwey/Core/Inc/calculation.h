/** ***************************************************************************
 * @file
 * @brief See calculation.c
 *
 * Prefix CALC
 *
 *****************************************************************************/

#ifndef CALCULATION_H_
#define CALCULATION_H_


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdbool.h>
#include <stdint.h>

/******************************************************************************
 * Defines
 *****************************************************************************/


/******************************************************************************
 * Types
 *****************************************************************************/
 /* enum for errors*/
typedef enum {
	CALC_ERROR_FREQUENCY = 0,
    CALC_ERROR_NONE
} CALC_ERROR_ITEM;

/* Structure for FFT*/
typedef struct {
    float main_freq;
    float signal_strength;
    CALC_ERROR_ITEM error;
} FFT;

/* Structure for distance and angle*/
typedef struct {
	float distance_r;
	float angle_r;
    float distance_l;
    float angle_l;
    float distance;
    float angle;
} DISTANCE_ANGLE;

/* Structure for Polynomial coefficients*/
typedef struct {
    float a_r;
    float b_r;
    float c_r;
    float a_l;
    float b_l;
    float c_l;
} POLY_COEFF;

/******************************************************************************
 * Functions
 *****************************************************************************/
FFT calculate_freq_and_signalstrength(uint8_t Channel, uint32_t* samples);
DISTANCE_ANGLE calculate_distance_and_angle(void);
uint32_t* calculate_average_of_measurements(void);

#endif	/* CALC_H_ */

