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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define ARM_MATH_CM4
#include "arm_math.h"

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
    float32_t main_freq;
    float32_t signal_strength;
    CALC_ERROR_ITEM error;
} FFT;

/* Structure for measurements*/
typedef struct {
	float32_t distance;
	float32_t angle;
	float32_t frequency;
	float32_t current;
} SINGLE_MEAS;

/* Structure for distance and angle*/
typedef struct {
	float32_t distance_r;
	float32_t distance_l;
	float32_t distance;
	float32_t angle;
} DISTANCE_ANGLE;

/* Structure for Polynomial coefficients (Calibration)*/
typedef struct {
	float32_t a_r;
	float32_t b_r;
	float32_t c_r;
	float32_t a_l;
	float32_t b_l;
	float32_t c_l;
} CALIBRATION;

/******************************************************************************
 * Functions
 *****************************************************************************/
FFT calculate_freq_and_signalstrength(float32_t input_samples[]);
SINGLE_MEAS single_measurement(uint32_t* samples);
DISTANCE_ANGLE calculate_distance_and_angle(float32_t signal_strength_r, float32_t signal_strength_l);
CALIBRATION start_calibration(float32_t distance[], float32_t signal_pr[], float32_t signal_pl[]);
void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c);


#endif	/* CALC_H_ */

