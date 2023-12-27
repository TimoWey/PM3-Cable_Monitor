/** ***************************************************************************
 * @file
 * @brief Calculations for displaying the measurements
 *
 *
 * Calculations for displaying the measurements
 * ====================================================
 *
 * Distance Calibration
 * -----------
 * - Calibration involves using the given distance between the board and the wire.
 * - Positioning of the board is crucial; it must be perpendicular to the wire during calibration.
 * - A ruler is employed for measuring the distance between the board and the wire.
 * - The calibration process includes taking three measurements per pad, which are executed through the GUI.
 * - Measurements are conducted at intervals of 10 mm, 50 mm, and 100 mm.
 * - For each pad and each set distance, the signal strength is recorded. See @ref calculate_freq_and_signalstrength for more details.
 * - For a visual representation of the calibration setup, refer to the diagram below.
 * @note Values are read from flash: @ref start_calibration
 * @see D_P Distance from the board center to pad
 *
 * @image html Doxygen/img/Calibration_Setup.png height=400px
 * 
 * Current Calibration
 * -----------
 * - Calibration involves using the given current through the wire, the type of cable (single or three-phase), and the distance
 * between the board and the wire.
 * - Positioning of the board is crucial; it must be perpendicular to the wire during calibration.
 * - A ruler is employed for measuring the distance between the board and the wire.
 * - The calibration process includes taking one measurement per hall-sensor, which are executed through the GUI.
 * - Measurements are conducted at different currents (1.2 A and 5 A) and different phases (single and three-phase).
 * - For each hall-sensor, current, and phase, the signal strength is recorded. See @ref calculate_freq_and_signalstrength for more details.
 * - For a visual representation of the calibration setup, refer to the diagram below.
 * @n Values are read from flash: @ref start_calibration
 *
 * @image html Doxygen/img/Calibration_Setup_current.png height=400px
 * 
 * Angle Calculation and Distance Approximation
 * -------
 * The equation for this trigonometry can be seen
 * under the figure.
 *
 * @image html Doxygen/img/Angle_Calculation.png height=400px
 *
 * @note The arctangent function, applied to calculate the angle between pad distance readings, 
 * maps any real number to an angle within -90 to 90 degrees, 
 * reflecting the ratio of pad distance value differences to the fixed pad separation, 
 * thereby facilitating the calculation of angles up to ±90 degrees. 
 * However, visualizing these angles as traditional triangles is challenging, 
 * as extreme sensor value differences — representing steep, 
 * nearly vertical angles — do not correspond neatly to standard geometric shapes.
 * That's why the visualization using standard geometric shapes
 * only allows angles between -45 and 45 degrees to be visualized.
 * Refer to the image above for a better understanding of the angle calculation.
 * 
 * @n signal_l: Signal strength of the left pad
 * @n signal_r: Signal strength of the right pad
 * 
 * Coefficients Used for Distance Approximation
 * ===================================
 * Distance
 * --------
 * Approximation is done with a Laurent polynomial of 2nd degree. 
 * @n By solving the equation system with the 3 measurements, the coefficients can be calculated.
 * Each coefficient is calculated with the following equation:
 * 
 * 
 * @image html Doxygen/img/distance_coefficients.png height=400px
 * @see calculate_coefficients_single_pad
 * 
 * The coefficients are calculated for each pad. With these coefficients, the distance can be approximated.
 * @ref calculate_distance_and_angle function calculates both distances from each pad
 * and returns the mean value of both distances as the real distance between the board center and the wire.
 * 
 * This approach allows the calibration and calculation to be done all on the board itself, 
 * instead of having to calculate the approximation externally using MATLAB and importing the values through a look-up table.
 * 
 * The approximation, in comparison to the look-up table approach, looks like this:
 * @image html Doxygen/img/approximation_plot.png height=600px
 * Using the coefficient approach, results in a very similar approximation to the look-up table approach, while being more efficient
 * and not requiring an external device to calculate the coefficients.
 * 
 * @n For calibration, only 3 measurements are needed.
 * @n d1, d2, d3: Distance for each measurement
 * @n s1, s2, s3: Signal for each measurement
 * @n a, b, c: @ref calculate_coefficients_single_pad
 *
 * Current Calculation
 * -------
 * Approximation is done with a constant, as seen in the figure.
 * @image html Doxygen/img/Current_Aproximation.png height=400px
 * This approach allows only an accurate approximation for a specific current in a very limited and close range.
 * \n The approximation is done for 1.2 A and 5 A.
 * \n The approximation is done for each pad and for each current.
 * \ As the phase changes the magnetic field, a different approximation is needed for each phase.
 * 
 * @n For calibration, only 1 measurement is needed per pad, set current (1.2 A or 5 A), and phase.
 * @n U: Signal
 * @n r: Distance from the board center to wire
 * @n const: @ref calculate_magnetic_coefficients
 *
 *
 * @todo Optimize accuracy of approximation
 * @todo Optimize output of accurate measurement
 * @todo Animate shutting off screen (Currently only static image)
 * 
 * @bug Current calculation sometimes returns NaN or inf values
 * 
 * ----------------------------------------------------------------------------
 * @author  Alejandro Horvat, horvaale@students.zhaw.ch
 * @date	26.12.2023
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
#include "arm_math.h"

/*******************************************************************************
 * Defines
 *****************************************************************************/
///< pad border to center of board 8.26 mm (Pad to Board Center) + 22.86 mm
///< (Board Width) / 2 = 19.69 mm (rounded to 19.7 mm)
#define D_P 19.7  ///< Distance from the board center to pad center
#define ACCURATE_MEASUREMENT_LOOPS 10  ///< How many loops for accu. meas.
#define CALIBRATION_MEASUREMENT_LOOPS 50  ///< How many loops for calibration meas
#define POW2(x) ((x) * (x))            ///< Power of two
#define ARM_MATH_CM4

/******************************************************************************
 * Variables
 *****************************************************************************/
static float32_t a_r = 0;
static float32_t b_r = 0;
static float32_t c_r = 0;

static float32_t a_l = 0;
static float32_t b_l = 0;
static float32_t c_l = 0;

static float32_t a_magn1_l_1P = 0;
static float32_t a_magn1_r_1P = 0;

static float32_t a_magn2_l_1P = 0;
static float32_t a_magn2_r_1P = 0;

static float32_t a_magn1_l_3P = 0;
static float32_t a_magn1_r_3P = 0;

static float32_t a_magn2_l_3P = 0;
static float32_t a_magn2_r_3P = 0;

bool State_BUZZER = true;
bool State_LED = true;

/******************************************************************************
 * Functions
 * ****************************************************************************/
void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c);
void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c);
void calculate_magnetic_coefficients(float32_t s, float32_t d, float32_t cal_current, float32_t* a_magn);
FFT calculate_freq_and_signalstrength(float32_t input_samples[]);
DISTANCE_ANGLE calculate_distance_and_angle(float32_t signal_strength_r, float32_t signal_strength_l);

/**
 * @brief Calculates the frequency and signal strength using Fast Fourier Transform (FFT).
 *
 * This function takes an array of input samples and performs the following steps:
 * 1. Removes the DC component from the input samples.
 * 2. Performs FFT on the input samples to obtain the complex output.
 * 3. Calculates the magnitude of the complex numbers.
 * 4. Finds the index of the maximum magnitude in the first half of the array.
 * 5. Determines the main frequency based on the maximum magnitude index.
 * 6. Rounds the main frequency to either 50 Hz or 60 Hz.
 * 7. Calculates the index of the rounded frequency.
 * 8. Calculates the signal strength at the rounded frequency.
 * 9. Returns the calculated main frequency and signal strength in a structure.
 * 
 * @param input_samples The array of input samples.
 * @return The structure containing the calculated main frequency and signal strength.
 * @see @a <a href="https://www.keil.com/pack/doc/CMSIS/DSP/html/index.html">CMSIS DSP Software Library </a>
 */
FFT calculate_freq_and_signalstrength(float32_t input_samples[])
{
    // remove DC component
    for (uint32_t i = 0; i < SAMPLE_LEN; i++) {
        input_samples[i] -= 2047.5;
    }
    // Create an array for the FFT output
    float32_t fft_complex_output[2 * SAMPLE_LEN];
    // Create an instance of the FFT structure
    arm_rfft_fast_instance_f32 fft_struct;
    // Initialize the FFT structure
    arm_rfft_fast_init_f32(&fft_struct, SAMPLE_LEN);
    // Perform the FFT on the input samples
    arm_rfft_fast_f32(&fft_struct, input_samples, fft_complex_output, 0);
    // Calculate magnitude of complex numbers
    arm_cmplx_mag_f32(fft_complex_output, fft_complex_output, SAMPLE_LEN / 2);
    // Find the index of the maximum magnitude in the first half of the array
    uint32_t maxIndex;
    float32_t maxValue;
    arm_max_f32(fft_complex_output, SAMPLE_LEN / 2, &maxValue, &maxIndex);
    // Create an instance of the FFT structure
    FFT fft;
    // Calculate the main frequency
    float main_frequency =
        (float)maxIndex * ((float)MEAS_get_samp_freq()) / SAMPLE_LEN;
    uint8_t given_frequency = 0;
    // Check if the main frequency is in the range of 45-55 Hz
    if (main_frequency <= 55 && main_frequency >= 45)
    {
        // If yes, round the given frequency to 50 Hz
        given_frequency = 50;
    }
    else if (main_frequency <= 65 && main_frequency >= 55)
    {
        // If yes, round the given frequency to 60 Hz
        given_frequency = 60;
    }
    else
    	given_frequency = 0;
    // calculate the index of the given frequency
    uint32_t index = (uint32_t)given_frequency * SAMPLE_LEN / MEAS_get_samp_freq();
    // set the signal strength to 0
    float signal_strength = 0;
    // check if the given frequency is 50 or 60 Hz
    if (given_frequency != 0)
    {
        // calculate the signal strength
        signal_strength = 2 * fft_complex_output[index] / SAMPLE_LEN;
        fft.error = CALC_ERROR_NONE;
    }
    else
    	fft.error = CALC_ERROR_FREQUENCY;  // if the given frequency is not 50 or 60 Hz
    // return the calculated values
    fft.main_freq = main_frequency;
    fft.signal_strength = signal_strength;
    return fft;
}

/**
 * @brief Performs accurate FFT calculation for signal strength and main frequency of each channel.
 *
 * This function calculates the signal strength and main frequency for each channel using FFT.
 * It performs accurate measurement loops and calculates the mean and standard deviation of the signal strength.
 * If the standard deviation is larger than 100, it sets the error flag accordingly.
 *
 * @return The calculated ACCU_FFT structure containing the signal strength, standard deviation, and error flag.
 */
ACCU_FFT accurate_FFT(void){
    // Create an instance of the ACCU_FFT structure
    ACCU_FFT accu_fft;
    // Create an instance of the FFT structure
    FFT fft;

    static float32_t accu_strength_PR[CALIBRATION_MEASUREMENT_LOOPS];
    static float32_t accu_strength_PL[CALIBRATION_MEASUREMENT_LOOPS];
    static float32_t accu_strength_HSR[CALIBRATION_MEASUREMENT_LOOPS];
    static float32_t accu_strength_HSL[CALIBRATION_MEASUREMENT_LOOPS];

    uint32_t* samples;

    static float32_t samples_PR[SAMPLE_LEN];
    static float32_t samples_PL[SAMPLE_LEN];
    static float32_t samples_HSR[SAMPLE_LEN];
    static float32_t samples_HSL[SAMPLE_LEN];

    for (uint8_t i = 0; i < CALIBRATION_MEASUREMENT_LOOPS; i++)
    {
        // Start the measurement
        samples = MEAS_start_measure();

        // Convert the samples to the specific channel
        for (uint32_t j = 0; j < SAMPLE_LEN; j++)
        {
            samples_PR[j] = (float32_t)samples[j * CHANNEL_NUM];
            samples_PL[j] = (float32_t)samples[j * CHANNEL_NUM + 1];
            samples_HSR[j] = (float32_t)samples[j * CHANNEL_NUM + 2];
            samples_HSL[j] = (float32_t)samples[j * CHANNEL_NUM + 3];
        }
        // Calculate the Signal Strength and the main frequency for each channel using FFT

        fft = calculate_freq_and_signalstrength(samples_PR);
        accu_strength_PR[i] = fft.signal_strength;
        fft = calculate_freq_and_signalstrength(samples_PL);
        accu_strength_PL[i] = fft.signal_strength;
        fft = calculate_freq_and_signalstrength(samples_HSR);
        accu_strength_HSR[i] = fft.signal_strength;
        fft = calculate_freq_and_signalstrength(samples_HSL);
        accu_strength_HSL[i] = fft.signal_strength;
        //current[i] = single_meas.current;
    }
    arm_mean_f32(accu_strength_PR, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_pr);
    arm_std_f32(accu_strength_PR, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_pr_std_dev);
    arm_mean_f32(accu_strength_PL, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_pl);
    arm_std_f32(accu_strength_PL, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_pl_std_dev);
    arm_mean_f32(accu_strength_HSR, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_hsr);
    arm_std_f32(accu_strength_HSR, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_hsr_std_dev);
    arm_mean_f32(accu_strength_HSL, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_hsl);
    arm_std_f32(accu_strength_HSL, CALIBRATION_MEASUREMENT_LOOPS, &accu_fft.signal_strength_hsl_std_dev);
    // Check if the standard deviation is larger than 100
    if (accu_fft.signal_strength_pr_std_dev > 100 || accu_fft.signal_strength_pl_std_dev > 100 \
    		|| accu_fft.signal_strength_hsr_std_dev > 100 || accu_fft.signal_strength_hsl_std_dev > 100)
        accu_fft.error = CALC_ERROR_DEVIATION_TOO_HIGH;
    else
    	accu_fft.error = CALC_ERROR_NONE;
    // Return the calculated values
    return accu_fft;
}

/**
 * @brief Perform a single measurement for a specific phase.
 *
 * This function starts the measurement, converts the samples to the specific channel,
 * calculates the signal strength and main frequency for each channel using FFT,
 * calculates the distance and angle, and calculates the current using the magnetic coefficients.
 * It also performs error testing and optimization on the calculated values.
 *
 * @param Phase The phase for which the measurement is performed (SINGLE_PHASE or THREE_PHASE).
 * @return The calculated values including frequency, distance, angle, current, and error status.
 */
SINGLE_MEAS single_measurement(uint8_t Phase)
{
    // Start the measurement
    uint32_t* samples = MEAS_start_measure();
    // Create an instance of the SINGLE_MEAS structure
    SINGLE_MEAS single_meas;
    // Create an instance of the FFT structure
    FFT fft;

    // Set the error to none
    single_meas.error = CALC_ERROR_NONE;

    static float32_t samples_PR[SAMPLE_LEN];
    static float32_t samples_PL[SAMPLE_LEN];
    static float32_t samples_HSR[SAMPLE_LEN];
    static float32_t samples_HSL[SAMPLE_LEN];

    float32_t current_l = 0;
    float32_t current_r = 0;

    // Convert the samples to the specific channel
    for (uint32_t i = 0; i < 64; i++)
    {
        samples_PR[i] = (float32_t)samples[(i * CHANNEL_NUM)];
        samples_PL[i] = (float32_t)samples[(i * CHANNEL_NUM) + 1];
        samples_HSR[i] = (float32_t)samples[(i * CHANNEL_NUM) + 2];
        samples_HSL[i] = (float32_t)samples[(i * CHANNEL_NUM) + 3];
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

    // Calculate the current using the magnetic coefficients for 5A
    if(Phase == SINGLE_PHASE)
    {
        current_l = a_magn2_l_1P * single_meas.distance * signal_strength_HSL;
        current_r = a_magn2_r_1P * single_meas.distance * signal_strength_HSR;
        single_meas.current = (current_l + current_r) / 2;
    }
    else if(Phase == THREE_PHASE)
    {
        if (signal_strength_HSL > signal_strength_HSR)
            single_meas.current = a_magn2_l_3P * single_meas.distance * signal_strength_HSL;
        else
            single_meas.current = a_magn2_r_3P * single_meas.distance * signal_strength_HSR;
    }

    // Check if the current is smaller than 4 A -> use the magnetic coefficients for 1.2 A
    if (single_meas.current < 4)
    {
        if(Phase == SINGLE_PHASE)
        {
            current_l = a_magn1_l_1P * single_meas.distance * signal_strength_HSL;
            current_r = a_magn1_r_1P * single_meas.distance * signal_strength_HSR;
            single_meas.current = (current_l + current_r) / 2;
        }
        else if(Phase == THREE_PHASE)
        {
            if (signal_strength_HSL > signal_strength_HSR)
                single_meas.current = a_magn1_l_3P * single_meas.distance * signal_strength_HSL;
            else
                single_meas.current = a_magn1_r_3P * single_meas.distance * signal_strength_HSR;
        }
    }

    // ERROR TESTING:

    // Check if distance is close enough for current calculation and if the current is out of the range of 0-10 A
    if (single_meas.distance > 20 || (single_meas.current <= 0 && single_meas.current >= 10))
       single_meas.error = CALC_ERROR_TOO_FAR_AWAY;

    // Check if the current is larger than 10 A -> CALL ERROR OVERCURRENT
    if (single_meas.current > 10)
       single_meas.error = CALC_ERROR_OVERCURRENT;

    // Check if the distance is larger than 300 mm or smaller than 0 -> CALL ERROR DISCONNECT
    if (single_meas.distance > 250)
    {
        single_meas.error = CALC_ERROR_DISCONNECT;
        single_meas.angle = 0;
    }

    // Check if the frequency is 0 -> CALL ERROR FREQUENCY
    if (single_meas.frequency == 0)
        single_meas.error = CALC_ERROR_FREQUENCY;

    // OPTIMIZE:
    // Limit the angle to +/- 90 degrees
    if (single_meas.angle > 90)
        single_meas.angle = 90;
    else if (single_meas.angle < -90)
        single_meas.angle = -90;

    // BUZZER LED
    if(single_meas.distance > 0 && single_meas.distance < 200 && (State_BUZZER == false))
       	TIM14->CCR1 = 50 + (single_meas.distance/4);
    else
    	TIM14->CCR1 = 0;

    if(single_meas.distance > 0 && single_meas.distance < 200 && (State_LED == false))
    	TIM5->CCR1 = abs(100 - (int)(single_meas.distance/2));
    else
       	TIM5->CCR1 = 0;
    // Return the calculated values
    return single_meas;
}

/**
 * @brief Performs accurate measurement of various parameters.
 *
 * This function calculates the mean value and standard deviation of distance, angle, frequency, and current
 * based on multiple single measurements. It checks for errors in the single measurements and sets the
 * appropriate error flags. If the standard deviation of any parameter exceeds 100, it sets the
 * error_accu flag to CALC_ERROR_DEVIATION_TOO_HIGH.
 *
 * @param Phase The phase for which the accurate measurement is performed.
 * @return ACCU_MEAS The structure containing the calculated values and error flags.
 */
ACCU_MEAS accurate_measurement(uint8_t Phase)
{
    // Create an instance of the ACCU_MEAS structure
    ACCU_MEAS accu_meas;

    // set the error to none
    accu_meas.error_accu = CALC_ERROR_NONE;

    static float32_t distance[ACCURATE_MEASUREMENT_LOOPS];
    static float32_t angle[ACCURATE_MEASUREMENT_LOOPS];
    static float32_t frequency[ACCURATE_MEASUREMENT_LOOPS];
    static float32_t current[ACCURATE_MEASUREMENT_LOOPS];

    for(uint8_t i = 0; i < ACCURATE_MEASUREMENT_LOOPS; i++){
        SINGLE_MEAS single_meas = single_measurement(Phase);
        distance[i] = single_meas.distance;
        angle[i] = single_meas.angle;
        frequency[i] = single_meas.frequency;
        current[i] = single_meas.current;

        // Check if there is an error in the single measurement
        if (single_meas.error != CALC_ERROR_NONE){
            accu_meas.error_single = single_meas.error;
        }
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
    arm_mean_f32(current, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.current);
    // Calculate standard deviation of the current
    arm_std_f32(current, ACCURATE_MEASUREMENT_LOOPS, &accu_meas.current_std_dev);

    // Check if the standard deviation is larger than 100
    if (accu_meas.distance_std_dev > 100 || accu_meas.angle_std_dev > 100 || \
    		accu_meas.frequency_std_dev > 100 || accu_meas.current_std_dev > 100)
        accu_meas.error_accu = CALC_ERROR_DEVIATION_TOO_HIGH;
    else
    	accu_meas.error_accu = CALC_ERROR_NONE;

    // Return the calculated values
    return accu_meas;
}

/**
 * @brief Calculates the distance and angle based on signal strengths.
 *
 * This function takes the signal strengths of the right and left signals and calculates
 * the distance and angle using predefined coefficients. The calculated values are stored
 * in a DISTANCE_ANGLE structure and returned.
 *
 * @param signal_strength_r The signal strength of the right signal.
 * @param signal_strength_l The signal strength of the left signal.
 * @return The calculated distance and angle.
 */
DISTANCE_ANGLE calculate_distance_and_angle(float32_t signal_strength_r, float32_t signal_strength_l)
{

    // Create an instance of the DISTANCE_ANGLE structure
    DISTANCE_ANGLE dist_angle;

    // Calculate the distance using the coefficients and the actual signal strength
    float32_t calc_distance = a_r + (b_r / signal_strength_r) + (c_r / POW2(signal_strength_r));
    // Set the calculated values
    dist_angle.distance_r = calc_distance;

    // Calculate the distance using the coefficients and the actual signal strength
    calc_distance = a_l + (b_l / signal_strength_l) + (c_l / POW2(signal_strength_l));
    // Set the calculated values
    dist_angle.distance_l = calc_distance;

    // Calculate the distance
    dist_angle.distance = (dist_angle.distance_l + dist_angle.distance_r) / 2;

    // Calculate the angle using the trigonometry
    dist_angle.angle = atanf((dist_angle.distance_l - dist_angle.distance_r) / (2 * D_P)) * (180 / PI);

    // Return the calculated values
    return dist_angle;
}

/**
 * @brief Starts the calibration process.
 *
 * This function initializes the necessary variables and arrays for calibration.
 * It calculates the coefficients for distance approximation and current approximation
 * based on the calibration data stored in flash memory.
 */
void start_calibration(void)
{
    // create an array of distance measurements
    static float32_t distance[3] = {10, 50, 100};

    // Measured current is 5 A and 1.2 A
    static float32_t current_1 = 5;
    float32_t current_2 = 1.2;

    // initialize arrays with values from the calibration (flash memory)
    float32_t signal_pl[3] = {Calibration_Data[0], Calibration_Data[1], Calibration_Data[2]};
    float32_t signal_pr[3] = {Calibration_Data[3], Calibration_Data[4], Calibration_Data[5]};
    float32_t signal_current_l_C1_1P = Calibration_Data[6];
    float32_t signal_current_l_C2_1P = Calibration_Data[7];
    float32_t signal_current_r_C1_1P = Calibration_Data[8];
    float32_t signal_current_r_C2_1P = Calibration_Data[9];
    float32_t signal_current_l_C1_3P = Calibration_Data[10];
    float32_t signal_current_l_C2_3P = Calibration_Data[11];
    float32_t signal_current_r_C1_3P = Calibration_Data[12];
    float32_t signal_current_r_C2_3P = Calibration_Data[13];

    // Calculate the coefficients for the distance approximation from a second degree polynomial
    calculate_coefficients_single_pad(signal_pr, distance, &a_r, &b_r, &c_r);
    calculate_coefficients_single_pad(signal_pl, distance, &a_l, &b_l, &c_l);
    // Calculate the coefficients for the current approximation from a constant
    calculate_magnetic_coefficients(signal_current_l_C1_1P, distance[0], current_1, &a_magn1_l_1P);
    calculate_magnetic_coefficients(signal_current_l_C2_1P, distance[0], current_2, &a_magn2_l_1P);
    calculate_magnetic_coefficients(signal_current_r_C1_1P, distance[0], current_1, &a_magn1_r_1P);
    calculate_magnetic_coefficients(signal_current_r_C2_1P, distance[0], current_2, &a_magn2_r_1P);
    calculate_magnetic_coefficients(signal_current_l_C1_3P, distance[0], current_1, &a_magn1_l_3P);
    calculate_magnetic_coefficients(signal_current_l_C2_3P, distance[0], current_2, &a_magn2_l_3P);
    calculate_magnetic_coefficients(signal_current_r_C1_3P, distance[0], current_1, &a_magn1_r_3P);
    calculate_magnetic_coefficients(signal_current_r_C2_3P, distance[0], current_2, &a_magn2_r_3P);
}

/**
 * Calculates the coefficients for the distance approximation from an approximation based on a second degree polynomial.
 *
 * @param s An array of three float32_t values representing x coordinates: x_0, x_1, x_2.
 * @param d An array of three float32_t values representing y coordinates: y_0, y_1, y_2.
 * @param a Pointer to a float32_t variable to store the calculated coefficient 'a'.
 * @param b Pointer to a float32_t variable to store the calculated coefficient 'b'.
 * @param c Pointer to a float32_t variable to store the calculated coefficient 'c'.
 */
void calculate_coefficients_single_pad(float32_t s[], float32_t d[], float32_t* a, float32_t* b, float32_t* c)
{
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

/**
 * @brief Calculates the magnetic coefficients.
 *
 * This function calculates the magnetic coefficients based on the given parameters.
 *
 * @param s The value of s.
 * @param d The value of d.
 * @param cal_current The calibration current.
 * @param a_magn Pointer to store the calculated magnetic coefficients.
 */
void calculate_magnetic_coefficients(float32_t s, float32_t d, float32_t cal_current, float32_t* a_magn)
{
    *a_magn = cal_current / (s * d);
}


/**
 * @brief Toggles the settings of the buzzer or LED based on the button number.
 *
 * This function toggles the settings of the buzzer or LED based on the button number.
 * If the button number is true, it toggles the buzzer settings. If the button number is false,
 * it toggles the LED settings. Also it enables or disables the buzzer or LED based on the
 * current settings.
 *
 * @param btn_nr The button number indicating whether to toggle the buzzer or LED settings.
 */
void toggle_Buzzer_settings(bool btn_nr)
{
	if(btn_nr == true)
	{
		if(State_BUZZER == true)
		{
			State_BUZZER = false;
			ENABLE_BUZZER();
		}
		else
		{
			State_BUZZER = true;
			DISABLE_BUZZER();
		}
	}
	else
	{
		if(State_LED == true)
		{
			State_LED = false;
			ENABLE_LED();
		}
		else
		{
			State_LED = true;
			DISABLE_LED();
		}
	}
}
