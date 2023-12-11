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
#include "stm32f4xx_hal.h"
//#include "arm_math.h"
#include "calculation.h"
#include "measuring.h"


#define ARM_MATH_CM4
#include "arm_math.h"

/** Struct with fields of a menu entry */
/*typedef struct {
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
///< pad border to center of board 8.26 mm (Pad to Board Center) + 22.86 mm (Board Width) / 2 = 19.69 mm (rounded to 19.7 mm)
#define D_P 19.7 ///< Distance from the board center to pad center
#define ACCURATE_MEASUREMENT_LOOPS 10 ///< How many loops for accu. meas.
#define POW2(x) ((x) * (x)) ///< Power of two

/******************************************************************************
 * Variables
 *****************************************************************************/


/******************************************************************************
 * Functions
 * ****************************************************************************/

/**
 * @brief Calculates the frequency and signal strength using Fast Fourier Transform (FFT).
 *
 * This function performs FFT on the input samples using the CMSIS-DSP library.
 * It calculates the magnitude of complex numbers and finds the index of the given frequency.
 * The signal strength is calculated based on the FFT output.
 * The main frequency is determined by finding the index of the maximum magnitude in the first half of the array.
 *
 * @param Channel The channel number.
 * @param samples Pointer to the input samples array.
 * @param given_frequency The given frequency.
 * @return FFT structure containing the main frequency and signal strength.
 */
FFT calculate_freq_and_signalstrength(uint8_t Channel, uint32_t* samples, uint8_t given_frequency) {
    // Perform FFT using CMSIS-DSP library
	uint8_t buffer_size = MEAS_get_num_of_samples();
    const uint32_t fft_size = buffer_size;
    // Convert the samples to the specific channel
    float32_t input_samples[buffer_size];
    for (uint32_t i = 0; i < fft_size; i++) {
        input_samples[i] = (float32_t)samples[i * MEAS_get_num_of_chan() + (Channel - 1)];
    }
    
    // remove DC component
    for (uint32_t i = 0; i < fft_size; i++) {
        input_samples[i] -= 2047.5;
    }

    // Create an array for the FFT output
    float32_t fft_complex_output[2*buffer_size];

    // Create an instance of the FFT structure
    arm_rfft_fast_instance_f32 fft_struct;

    // Initialize the FFT structure
    arm_rfft_fast_init_f32(&fft_struct, fft_size);

    // Perform the FFT on the input samples
    arm_rfft_fast_f32(&fft_struct, input_samples, fft_complex_output, 0);

    // Calculate magnitude of complex numbers
    arm_cmplx_mag_f32(fft_complex_output, fft_complex_output, fft_size / 2);

    //calculate the index of the given frequency
    uint32_t index = (uint32_t)given_frequency * fft_size / MEAS_get_samp_freq();

    //calculate the signal strength
    float signal_strength = 2* fft_complex_output[index] / fft_size;

    // Find the index of the maximum magnitude in the first half of the array
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(fft_complex_output, fft_size / 2, &maxValue, &maxIndex);

    // Calculate the main frequency
    float main_frequency = (float)maxIndex * ((float)MEAS_get_samp_freq()) / fft_size;

    // Create an instance of the FFT structure
    FFT fft;

    // return the calculated values
    fft.main_freq = main_frequency;
    fft.signal_strength = signal_strength;
    return fft;
}

//DISTANCE_ANGLE calculate_distance_and_angle_single_pad(float distance_r, float distance_l){
//
//
//}
