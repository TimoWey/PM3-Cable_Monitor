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
#define SAMPLE_LEN 64
#define CHANNEL_NUM 4

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

/* Structure for Accurate FFT*/
typedef struct {
    float32_t signal_strength_pr;
    float32_t signal_strength_pr_std_dev;
    float32_t signal_strength_pl;
    float32_t signal_strength_pl_std_dev;
    float32_t signal_strength_hsr;
    float32_t signal_strength_hsr_std_dev;
    float32_t signal_strength_hsl;
    float32_t signal_strength_hsl_std_dev;
} ACCU_FFT;

/* Structure for measurements*/
typedef struct {
	float32_t distance;
	float32_t angle;
	float32_t frequency;
	float32_t current;
} SINGLE_MEAS;

/* Structure for accurate measurements*/
typedef struct {
	float32_t distance;
	float32_t angle;
	float32_t frequency;
	float32_t current;
    float32_t distance_std_dev;
    float32_t angle_std_dev;
    float32_t frequency_std_dev;
} ACCU_MEAS;

/* Structure for distance and angle*/
typedef struct {
	float32_t distance_r;
	float32_t distance_l;
	float32_t distance;
	float32_t angle;
} DISTANCE_ANGLE;

/******************************************************************************
 * Functions
 *****************************************************************************/
SINGLE_MEAS single_measurement(void);
ACCU_MEAS accurate_measurement(void);
ACCU_FFT accurate_FFT(void);
void start_calibration(void);

/******************************************************************************
 * External variables (FLASH)
 *****************************************************************************/

extern uint32_t Calibration_Data[12];

#endif	/* CALC_H_ */

