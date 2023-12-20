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
#include <stdbool.h>
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

*******************************************************************************
 * Defines
 *****************************************************************************/
///< pad border to center of board 8.26 mm (Pad to Board Center) + 22.86 mm
///< (Board Width) / 2 = 19.69 mm (rounded to 19.7 mm)
#define D_P 19.7  ///< Distance from the board center to pad center
#define ACCURATE_MEASUREMENT_LOOPS 50  ///< How many loops for accu. meas.
#define POW2(x) ((x) * (x))            ///< Power of two

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 * ****************************************************************************/

void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c);
FFT calculate_freq_and_signalstrength(float32_t input_samples[]);
DISTANCE_ANGLE calculate_distance_and_angle(float32_t signal_strength_r, float32_t signal_strength_l);
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
FFT calculate_freq_and_signalstrength(float32_t input_samples[]) {
    // Perform FFT using CMSIS-DSP library
    const uint8_t fft_size = MEAS_get_num_of_samples();
    // remove DC component
    for (uint32_t i = 0; i < fft_size; i++) {
        input_samples[i] -= 2047.5;
    }
    // Create an array for the FFT output
    float32_t fft_complex_output[2 * fft_size];
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


SINGLE_MEAS single_measurement(uint32_t* samples) {
    // Create an instance of the SINGLE_MEAS structure
    SINGLE_MEAS single_meas;
    // Create an instance of the FFT structure
    FFT fft;

    uint8_t buffer_size = MEAS_get_num_of_samples();
    float32_t samples_PR[buffer_size];
    float32_t samples_PL[buffer_size];
    float32_t samples_HSR[buffer_size];
    float32_t samples_HSL[buffer_size];

    // Convert the samples to the specific channel
    for (uint32_t i = 0; i < buffer_size; i++) {
        samples_PR[i] = (float32_t)samples[i * MEAS_get_num_of_chan()];
        samples_PL[i] = (float32_t)samples[i * MEAS_get_num_of_chan() + 1];
        samples_HSR[i] = (float32_t)samples[i * MEAS_get_num_of_chan() + 2];
        samples_HSL[i] = (float32_t)samples[i * MEAS_get_num_of_chan() + 3];
    }
    // Calculate the Signal Strength and the main frequency for each channel using FFT
    fft = calculate_freq_and_signalstrength(samples_PR);
    float32_t signal_strength_PR = fft.signal_strength;
    float32_t main_frequency_PR = fft.main_freq;
    fft = calculate_freq_and_signalstrength(samples_PL);
    float32_t signal_strength_PL = fft.signal_strength;
    float32_t main_frequency_PL = fft.main_freq;
    fft = calculate_freq_and_signalstrength(samples_HSR);
    float32_t signal_strength_HSR = fft.signal_strength;
    fft = calculate_freq_and_signalstrength(samples_HSL);
    float32_t signal_strength_HSL = fft.signal_strength;
    // Calculate the main frequency
    single_meas.frequency = (main_frequency_PR + main_frequency_PL) / 2;
    // Calculate distance and angle
    DISTANCE_ANGLE dist_angle = calculate_distance_and_angle(signal_strength_PR, signal_strength_PL);
    single_meas.distance = dist_angle.distance;
    single_meas.angle = dist_angle.angle;

    // TODO: Calculate current
    single_meas.current = 0;

    return single_meas;
}

ACCU_MEAS accurate_measurement(uint32_t* samples){
    // Create an instance of the ACCU_MEAS structure
    ACCU_MEAS accu_meas;
    // Create an instance of the FFT structure

    float32_t distance[ACCURATE_MEASUREMENT_LOOPS];
    float32_t angle[ACCURATE_MEASUREMENT_LOOPS];
    float32_t frequency[ACCURATE_MEASUREMENT_LOOPS];

    //float32_t current[ACCU_MEASUREMENT_LOOPS];
    for(uint8_t i = 0; i < ACCURATE_MEASUREMENT_LOOPS; i++){
        SINGLE_MEAS single_meas = single_measurement(samples);
        distance[i] = single_meas.distance;
        angle[i] = single_meas.angle;
        frequency[i] = single_meas.frequency;
        //current[i] = single_meas.current;
    }
    // Calculate the mean value of the distance
    arm_mean_f32(distance, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.distance);
    // Calculate standard deviation of the distance
    arm_std_f32(distance, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.distance_std_dev);
    // Calculate the mean value of the angle
    arm_mean_f32(angle, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.angle);
    // Calculate standard deviation of the angle
    arm_std_f32(angle, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.angle_std_dev);
    // Calculate the mean value of the frequency
    arm_mean_f32(frequency, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.frequency);
    // Calculate standard deviation of the frequency
    arm_std_f32(frequency, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.frequency_std_dev);
    // Calculate the mean value of the current
    //arm_mean_f32(current, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.current);
    // Calculate standard deviation of the current
    //arm_std_f32(current, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.current_std_dev);
    return accu_meas;
}
DISTANCE_ANGLE calculate_distance_and_angle(float32_t signal_strength_r, float32_t signal_strength_l){
    // TODO: Put Calibration Values in another function
    float32_t distance[3] = {10, 50, 100};
    float32_t signal_r[3] = {1030, 717, 543};
    float32_t signal_l[3] = {920, 655, 553};

    // Create an instance of the CALIBRATION structure
	CALIBRATION calibration = start_calibration(distance, signal_r, signal_l);

    // Create an instance of the DISTANCE_ANGLE structure
    DISTANCE_ANGLE dist_angle;

    // Calculate the distance using the coefficients and the actual signal strength
    float32_t calc_distance = calibration.a_r + (calibration.b_r / signal_strength_r) + (calibration.c_r / POW2(signal_strength_r));
    // Set the calculated values
    dist_angle.distance_r = calc_distance;

    // Calculate the distance using the coefficients and the actual signal strength
    calc_distance = calibration.a_l + (calibration.b_l / signal_strength_l) + (calibration.c_l / POW2(signal_strength_l));
    // Set the calculated values
    dist_angle.distance_l = calc_distance;

    // Calculate the distance
    dist_angle.distance = (dist_angle.distance_l + dist_angle.distance_r) / 2;

    // Calculate the angle using the trigonometry
    dist_angle.angle = atanf((dist_angle.distance_l - dist_angle.distance_r) / (2 * D_P)) * (180 / PI);

    // Return the calculated values
    return dist_angle;
}

CALIBRATION start_calibration(float32_t distance[], float32_t signal_pr[], float32_t signal_pl[]) // TODO: add Hall sensor Calibration/Coefficients
{
    // create an instance of the CALIBRATION structure
    CALIBRATION calibration;

    // Calculate the coefficients for the distance approximation from a second degree polynomial
    calculate_coefficients_single_pad(signal_pr, distance, &calibration.a_r, &calibration.b_r, &calibration.c_r);
    calculate_coefficients_single_pad(signal_pl, distance, &calibration.a_l, &calibration.b_l, &calibration.c_l);

    return calibration;
}

/**
 * Calculates the coefficients for the distance approximation from an approximation based on a second degree polynomial.
 *
 * @param s An array containing the values x_0, x_1, x_2.
 * @param d An array containing the values y_0, y_1, y_2.
 */
void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c) {
    // s = x_0, x_1, x_2 d= y_0, y_1, y_2
    // Calculate the coefficients for the distance approximation from an approximation based on a second degree polynomial
    // a=((x_0^(2)*(x_1-x_2)*y_0-x_0*(x_1^(2)*y_1-x_2^(2)*y_2)+x_1*(x_1*y_1-x_2*y_2)*x_2)/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))
    // -> Result of Nspire CAS
    
    *a = (POW2(s[0]) * (s[1] - s[2]) * d[0] - s[0] * (POW2(s[1]) * d[1] - POW2(s[2]) * d[2]) + s[1] * (s[1] * d[1] - s[2] * d[2]) * s[2])
    / ((POW2(s[0]) - s[0] * (s[1] + s[2]) + s[1] * s[2]) * (s[1] - s[2]));
    // b = ((−(x_0^(2)*(x_1^(2)*(y_0-y_1)-x_2^(2)*(y_0-y_2))+x_1^(2)*x_2^(2)*(y_1-y_2)))/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))
    // -> Result of Nspire CAS

    *b = (-(POW2(s[0]) * (POW2(s[1]) * (d[0] - d[1]) - POW2(s[2]) * (d[0] - d[2])) + POW2(s[1]) * POW2(s[2]) * (d[1] - d[2])))
    / ((POW2(s[0]) - s[0] * (s[1] + s[2]) + s[1] * s[2]) * (s[1] - s[2]));

    // c=((x_0*(x_0*(x_1*(y_0-y_1)-x_2*(y_0-y_2))+x_1*x_2*(y_1-y_2))*x_1*x_2)/((x_0^(2)-x_0*(x_1+x_2)+x_1*x_2)*(x_1-x_2)))
    // -> Result of Nspire CAS
    *c = ((s[0] * (s[0] * (s[1] * (d[0] - d[1]) - s[2] * (d[0] - d[2])) + s[1] * s[2] * (d[1] - d[2])) * s[1] * s[2]))
    / ((POW2(s[0]) - s[0] * (s[1] + s[2]) + s[1] * s[2]) * (s[1] - s[2]));
}
