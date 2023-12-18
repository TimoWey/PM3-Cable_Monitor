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
 * @todo Accurate Measurement, Angle Calculation, Current Calculation, Calibration Pad, Calibration Hall Sensor
 * ----------------------------------------------------------------------------
 * @author  Alejandro Horvat, horvaale@students.zhaw.ch
 * @date	12.28.2021
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "calculation.h"
#include <stdint.h>
#include <stdio.h>
#include "measuring.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

#define ARM_MATH_CM4
#include "arm_math.h"

/** Struct with fields of a menu entry */
/*typedef struct {
        float distance; 			///< Distance from wire to board
center in mm float angle; 				///< Angle pointing to
wire in degree float current; 				///< Current flowing
through wire in A float dist_sdev; 			///< Distance standard
devision in mm float angl_sdev; 			///< Angle standard
devision in degree float curr_sdev; 			///< Current standard
devision in A CALC_error_item_t error;	///< Measurement error }
CALC_meas_data_t;

/******************************************************************************
 * Defines
 *****************************************************************************/
///< pad border to center of board 8.26 mm (Pad to Board Center) + 22.86 mm
///< (Board Width) / 2 = 19.69 mm (rounded to 19.7 mm)
#define D_P 19.7  ///< Distance from the board center to pad center
#define ACCURATE_MEASUREMENT_LOOPS 10  ///< How many loops for accu. meas.
#define POW2(x) ((x) * (x))            ///< Power of two

/******************************************************************************
 * Variables
 *****************************************************************************/
static float a = 0;  ///< Coefficient for distance approximation
static float b = 0;  ///< Coefficient for distance approximation
static float c = 0;  ///< Coefficient for distance approximation

/******************************************************************************
 * Functions
 * ****************************************************************************/

/**
 * @brief Calculates the frequency and signal strength using FFT.
 *
 * This function performs Fast Fourier Transform (FFT) on the input samples to
 *calculate the main frequency and signal strength. It uses the CMSIS-DSP
 *library for FFT calculations.
 *
 * @param Channel The channel number for which the frequency and signal strength
 *are calculated.
 * @param samples Pointer to the array of input samples.
 * @return FFT structure containing the calculated main frequency and signal
 *strength.
 **/
FFT calculate_freq_and_signalstrength(uint8_t Channel, uint32_t* samples) {
    // Perform FFT using CMSIS-DSP library
    uint8_t buffer_size = MEAS_get_num_of_samples();
    const uint32_t fft_size = buffer_size;
    // Convert the samples to the specific channel
    float32_t input_samples[buffer_size];
    for (uint32_t i = 0; i < fft_size; i++) {
        input_samples[i] =
            (float32_t)samples[i * MEAS_get_num_of_chan() + (Channel - 1)];
    }
    // remove DC component
    for (uint32_t i = 0; i < fft_size; i++) {
        input_samples[i] -= 2047.5;
    }
    // Create an array for the FFT output
    float32_t fft_complex_output[2 * buffer_size];
    // Create an instance of the FFT structure
    arm_rfft_fast_instance_f32 fft_struct;
    // Initialize the FFT structure
    arm_rfft_fast_init_f32(&fft_struct, fft_size);
    // Perform the FFT on the input samples
    arm_rfft_fast_f32(&fft_struct, input_samples, fft_complex_output, 0);
    // Calculate magnitude of complex numbers
    arm_cmplx_mag_f32(fft_complex_output, fft_complex_output, fft_size / 2);
    // Find the index of the maximum magnitude in the first half of the array
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(fft_complex_output, fft_size / 2, &maxValue, &maxIndex);
    // Create an instance of the FFT structure
    FFT fft;
    // Calculate the main frequency
    float main_frequency =
        (float)maxIndex * ((float)MEAS_get_samp_freq()) / fft_size;
    uint8_t given_frequency = 0;
    // Check if the main frequency is in the range of 45-55 Hz
    if (main_frequency <= 55 && main_frequency >= 45) {
        // If yes, round the given frequency to 50 Hz
        given_frequency = 50;
    } else if (main_frequency <= 65 && main_frequency >= 55) {
        // If yes, round the given frequency to 60 Hz
        given_frequency = 60;
    } else given_frequency = 0;
    // calculate the index of the given frequency
    uint32_t index = (uint32_t)given_frequency * fft_size / MEAS_get_samp_freq();
    // set the signal strength to 0
    float signal_strength = 0; 
    // check if the given frequency is 50 or 60 Hz
    if (given_frequency != 0) {
        // calculate the signal strength
        signal_strength = 2 * fft_complex_output[index] / fft_size;
        fft.error = CALC_ERROR_NONE;
    } else fft.error = CALC_ERROR_FREQUENCY;  // if the given frequency is not 50 or 60 Hz
    // return the calculated values
    fft.main_freq = main_frequency;
    fft.signal_strength = signal_strength;
    return fft;
}


/**
 * @brief Calculates the coefficients for the distance approximation from a second degree polynomial.
 *
 * This function calculates the coefficients (a, b, c) for the distance approximation from a second degree polynomial
 * using the given input arrays (d, s).
 *
 * @param d An array of float32_t values representing the distance values.
 * @param s An array of float32_t values representing the sensor values.
 */
void calculate_coefficients_single_pad(float32_t d[], float32_t s[]) {
    // Calculate the coefficients for the distance approximation from a second degree polynomial

    /*  a=((−(x_0*(y_1-y_2)-x_1*(y_0-y_2)+x_2*(y_0-y_1)))/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))
        -> Result from Nspire
    */

    a = ((-(s[0] * (d[1] - d[2]) - s[1] * (d[0] - d[2]) + s[2] * (d[0] - d[1])))) /
                    ((POW2(s[0]) - s[0]*(s[1]+s[2]) + s[1]*s[2])*(s[1]-s[2]));

    /*  b=((x_0^(2)*(y_1-y_2)-x_1^(2)*(y_0-y_2)+x_2^(2)*(y_0-y_1))/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))  
        -> Result from Nspire
    */

    b = ((POW2(s[0]) * (d[1] - d[2])) - (POW2(s[1]) * (d[0] - d[2])) + (POW2(s[2]) * (d[0] - d[1]))) /
                    ((POW2(s[0]) - s[0]*(s[1]+s[2]) + s[1]*s[2])*(s[1]-s[2]));

    /*  c=((x_0^(2)*(x_1*y_2-x_2*y_1)-x_0*(x_1^(2)*y_2-x_2^(2)*y_1)+x_1*(x_1-x_2)*x_2*y_0)/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))
        -> Result from Nspire
    */   

    c = ((POW2(s[0]) * (s[1] * d[2] - s[2] * d[1])) - (s[0] * (POW2(s[1]) * d[2] - POW2(s[2]) * d[1])) + (s[1] * (s[1] - s[2]) * s[2] * d[0])) /
                    ((POW2(s[0]) - s[0]*(s[1]+s[2]) + s[1]*s[2])*(s[1]-s[2]));
}

DISTANCE_ANGLE calculate_distance_and_angle()
{ 
    float32_t distance[3] = {10, 50, 100};
    float32_t signal_r[3] = {1030, 717, 543};
    float32_t signal_l[3] = {920, 655, 553};

    // Create an instance of the POLY_COEFF structure
    POLY_COEFF poly_coeff;
    // Create an instance of the DISTANCE_ANGLE structure
    DISTANCE_ANGLE dist_angle;

    // Calculate the coefficients for the distance approximation from a second degree polynomial
    calculate_coefficients_single_pad(distance, signal_r);
    poly_coeff.a_r = a;
    poly_coeff.b_r = b;
    poly_coeff.c_r = c;

    calculate_coefficients_single_pad(distance, signal_l);
    poly_coeff.a_l = a;
    poly_coeff.b_l = b;
    poly_coeff.c_l = c;

    // measure the signal strength and calculate the distance and angle
    uint32_t* Samples = MEAS_start_measure();
    FFT fft = calculate_freq_and_signalstrength(1, Samples);

    float32_t signal_pad_right = fft.signal_strength;
    // Calculate the distance using the coefficients and the actual signal strength
    float32_t calc_distance = a * POW2(signal_pad_right) + b * signal_pad_right + c;

    // Calculate the angle using the distance
    float32_t angle = atanf(calc_distance / D_P) * 180 / PI;
    // Set the calculated values
    dist_angle.distance_r = calc_distance;
    dist_angle.angle_r = angle;

    fft = calculate_freq_and_signalstrength(2, Samples);
    signal_pad_right = fft.signal_strength;
    // Calculate the distance using the coefficients and the actual signal strength
    calc_distance = a * POW2(signal_pad_right) + b * signal_pad_right + c;
    // Calculate the angle using the distance
    angle = atanf(calc_distance / D_P) * 180 / PI;
    // Set the calculated values
    dist_angle.distance_l = calc_distance;
    dist_angle.angle_l = angle;

    angle = (dist_angle.angle_r + dist_angle.angle_l) / 2;

    if (dist_angle.distance_r < dist_angle.distance_l) {
        angle = -angle;
	}
    
    // calculate the distance and angle from the center of board to the wire
    dist_angle.distance = (dist_angle.distance_r + dist_angle.distance_l) / 2;
    dist_angle.angle = angle;
    
    // Return the calculated values
    return dist_angle;
}
