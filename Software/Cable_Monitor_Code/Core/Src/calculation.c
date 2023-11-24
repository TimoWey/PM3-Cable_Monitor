/** ***************************************************************************
 * @file
 * @brief Calculations for displaying the measurements
 *
 *
 * Trigonometry used for distance and angle calculation
 * ====================================================
 *
 * Calibration
 * -----------
 * For calibration the angle is given, because
 * the board is placed perpendicular to the wire.
 * @n The equation for this trigonometry can be seen
 * under the figure.
 * @n d: Distance from wire to pad (left or right)
 * @n l: Distance from the board center to wire
 * @n x: Distance from the board center to pad
 * @see D_P Distance from the board center to pad
 * 
 * @image html trigonometry_calibration.jpg
 * 
 * Measure
 * -------
 * The equation for this trigonometry can be seen
 * under the figure.
 * 
 * @image html trigonometry_measure.jpg
 *
 *
 * Approximation used for calculations
 * ===================================
 * Distance
 * --------
 * Approximation is done with a Laurent polynomial 2nd degree.
 * @n For calibration only 3 measurements are needed.
 * @n d1,d2,d3: Distance for each measurement
 * @n s1,s2,s3: Signal for each measurement
 * @n a,b,c: @ref Coefficients for distance approximation
 *
 * @image html approximation_coefficient.jpg
 *
 * Current
 * -------
 * Approximation is done with a constant as seen in the figure.
 * @n For calibration only 1 measurements is needed.
 * @n U: Signal
 * @n r: Distance from the board center to wire
 * @n const: @ref Constant for current approximation.
 *
 * @image html approximation_constant.jpg
 *
 * ----------------------------------------------------------------------------
 * @author  Alejandro Horvat, horvaale@students.zhaw.ch
 * @date	12.28.2021
 *****************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "arm_math.h"

#include "calculation.h"
#include "measuring.h"

/** Struct with fields of a menu entry */
typedef struct {
	float distance; 			///< Distance from wire to board center in mm
	float angle; 				///< Angle pointing to wire in degree
	float current; 				///< Current flowing through wire in A
	float dist_sdev; 			///< Distance standard devision in mm
	float angl_sdev; 			///< Angle standard devision in degree
	float curr_sdev; 			///< Current standard devision in A
	CALC_error_item_t error;	///< Measurement error
} CALC_meas_data_t;

/******************************************************************************
 * Defines
 *****************************************************************************/
#define D_P 18 ///< Distance board center to pad
#define ACCURATE_MEASUREMENT_LOOPS 10 ///< How many loops for accu. meas.
#define POW2(x) ((x) * (x)) ///< Power of two

/******************************************************************************
 * Variables
 *****************************************************************************/
static float cal_distance[CALC_CALI_P_END - 3] = {10, 100, 300};
	///< Distance from wire to board center
static float cal_current[CALC_CALI_C_END - 3] = {5}; ///< Current through wire

/** @todo safe in EEPROM in a future version */
static float a_static_l = 0;
	///< Coefficient for distance approximation @anchor Coefficients
/** @todo safe in EEPROM in a future version */
static float b_static_l = 0; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float c_static_l = 0; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float a_static_r = 0; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float b_static_r = 0; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float c_static_r = 0; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float a_magnetic_1 = 0;
	///< Constant for Current approximation @anchor Constant
/** @todo safe in EEPROM in a future version */
static float a_magnetic_3 = 0;
	///< Constant for Current approximation

/******************************************************************************
 * Functions
 * ****************************************************************************/
static float calc_signal_strength(float *rfft_input, uint8_t fft_len,
								uint8_t frequency);
static void calc_distance_and_angle_from_one_side(float distance_pad_1,
                                float distance_pad_2, float *distance_center,
                                float *angle);
static void calc_distance_and_angle(float distance_pad_l,
								float distance_pad_r, float *distance_center,
                                float *angle);