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
 * @author  Flavio Felder, feldefla@students.zhaw.ch
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
static float a_static_l = -43.14;
	///< Coefficient for distance approximation @anchor Coefficients
/** @todo safe in EEPROM in a future version */
static float b_static_l = 35.98e3; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float c_static_l = -161.1e3; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float a_static_r = -73.23; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float b_static_r = 61.36e3; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float c_static_r = -1.981e6; ///< Coefficient for distance approximation
/** @todo safe in EEPROM in a future version */
static float a_magnetic_1 = 581.5586e-6;
	///< Constant for Current approximation @anchor Constant
/** @todo safe in EEPROM in a future version */
static float a_magnetic_3 = 181.5586e-6;
	///< Constant for Current approximation


/******************************************************************************
 * Functions
 *****************************************************************************/
static float CALC_get_signalstrength(float *rfft_input, uint8_t fft_len,
								uint8_t frequency);
static void CALC_calc_distance_and_angle_from_one_side(float distance_pad_1,
                                float distance_pad_2, float *distance_center,
                                float *angle);
static void CALC_calc_distance_and_angle(float distance_pad_l,
								float distance_pad_r, float *distance_center,
                                float *angle);


/** ***************************************************************************
 * @brief Calculate signal strength in the frequency domain
 * @param[in] *rfft_input	Array of signal
 * @param[in] fft_len		Length of array
 * @param[in] frequency		Amplitude at this frequency
 * @return Amplitude in 3.3V/4096
 * 
 * @note To get an optimal result from the FFT, sampling has to be done over a
 * whole number of signal periods (prevent the so called leakage effect).
 * E.g. sampling over 100ms spans exactly 5 periods of 50Hz.
 * @note The FFT needs block sizes of a power of 2. E.g. N = 64 samples.
 * Combined with N∙Ts = 100ms defines the
 * sampling frequency fs = 64/100ms = 640Hz
 *****************************************************************************/
static float CALC_get_signalstrength(float *rfft_input, uint8_t fft_len,
                                uint8_t frequency)
{
    const uint16_t samplingFreq = MEAS_get_samp_freq();
    arm_rfft_fast_instance_f32 fft_structer;
    float rfft_cmplx_output[fft_len];
    uint8_t fft_index = frequency / (samplingFreq / fft_len);
    float rfft_mag_output[fft_len];

    arm_rfft_fast_init_f32(&fft_structer, fft_len);
    arm_rfft_fast_f32(&fft_structer, rfft_input, rfft_cmplx_output, 0);
    /* Calculate magnitude of complex coefficients (2* at return) */
    arm_cmplx_mag_f32(rfft_cmplx_output, rfft_mag_output, fft_len / 2);

    return (2 * rfft_mag_output[fft_index] / fft_len);
}


/** ***************************************************************************
 * @brief Calculate angle and distance to board center from one side
 * @param[in] distance_pad_1		Distance from wire to pad
 * @param[in] distance_pad_2		Distance from wire to pad
 * @param[out] *distance_center		Distance from wire to board center
 * @param[out] *angle				Angle pointing to wire in degree
 * 
 * @note Angle always positiv
 * @bug Skips small angles at short distances
 *****************************************************************************/
static void CALC_calc_distance_and_angle_from_one_side(float distance_pad_1,
                                float distance_pad_2, float *distance_center,
                                float *angle)
{
    float cos_a;  // Ratio needed for calculation

    /* Divide by 5 to compensate that pad signal increases at an angle */
    cos_a = (POW2(distance_pad_2) + POW2(2 * D_P) - POW2(distance_pad_1)) /
            (2 * distance_pad_2 * 2 * D_P) / 5;
    if (cos_a < -1) {
        cos_a = -1;
	}
    if (1 < cos_a) {
        cos_a = 1;
	}

    if ((POW2(distance_pad_2) + POW2(D_P) - 2 * distance_pad_2 * D_P * cos_a) <
        0.0001) {
        (*distance_center) = 0.0001;
    } else {
        (*distance_center) = sqrtf(POW2(distance_pad_2) + POW2(D_P) -
                                   2 * distance_pad_2 * D_P * cos_a);
    }

    (*angle) = distance_pad_2 / (*distance_center) * sinf(acosf(cos_a));
    if ((*angle) < -1) {
        (*angle) = -1;
	}
    if (1 < (*angle)) {
        (*angle) = 1;
	}
    (*angle) = asinf((*angle)) * (180 / PI) - 90;
}


/** ***************************************************************************
 * @brief Calculate angle and distance to board center
 * @param[in] distance_pad_l		Left distance from wire to pad
 * @param[in] distance_pad_r		Right distance from wire to pad
 * @param[out] *distance_center		Distance from wire to board center
 * @param[out] *angle				Angle pointing to wire in degree
 *****************************************************************************/
static void CALC_calc_distance_and_angle(float distance_pad_l,
                                float distance_pad_r, float *distance_center,
                                float *angle)
{
    float d1, d2;  // Distance from wire to board center
    float a1, a2;  // Angle pointing to wire
    CALC_calc_distance_and_angle_from_one_side(distance_pad_l, distance_pad_r,
    									&d1, &a1);
    CALC_calc_distance_and_angle_from_one_side(distance_pad_r, distance_pad_l,
    									&d2, &a2);

    *distance_center = (d1 + d2) / 2;
    *angle = (a1 + a2) / 2;

    /* Determine in which direction the angle points */
    if (distance_pad_r < distance_pad_l) {
        *angle = -*angle;
	}
}


/** ***************************************************************************
 * @brief Single measurement
 * @param[out] *meas_data	Measurement data @see CALC_meas_data_t
 * @param[in]  phase		Select which phase mode for measurement
 *
 * @note Standard deviation in data will not be changed.
 *****************************************************************************/
void CALC_start_single_measurement(CALC_meas_data_t *meas_data, CALC_phase_item_t phase)
{
    uint8_t num_of_chan = MEAS_get_num_of_chan();
    uint8_t fft_len = MEAS_get_num_of_samples();
    uint32_t *ADC_samples = MEAS_start_meas();

    meas_data->error = CALC_ERROR_NONE;

    /* Split samples and convert to float */
    float ADC_samples_pad_r[fft_len];   // IN13 	PAD_RIGHT
    float ADC_samples_pad_l[fft_len];   // IN4  	PAD_LEFT
    float ADC_samples_coil_r[fft_len];  // IN11	COIL_RIGHT
    float ADC_samples_coil_l[fft_len];  // IN6	COIL_LEFT
    for (uint8_t i = 0; i < fft_len; i++) {
        ADC_samples_pad_r[i] = (float)ADC_samples[num_of_chan * i];
        ADC_samples_pad_l[i] = (float)ADC_samples[num_of_chan * i + 1];
        ADC_samples_coil_r[i] = (float)ADC_samples[num_of_chan * i + 2];
        ADC_samples_coil_l[i] = (float)ADC_samples[num_of_chan * i + 3];
    }

    /* 50Hz filtered signal strength */
    float signal_pad_r = CALC_get_signalstrength(ADC_samples_pad_r, fft_len, 50);
    float signal_pad_l = CALC_get_signalstrength(ADC_samples_pad_l, fft_len, 50);
    float signal_coil_r = CALC_get_signalstrength(ADC_samples_coil_r, fft_len, 50);
    float signal_coil_l = CALC_get_signalstrength(ADC_samples_coil_l, fft_len, 50);

    /* Approximate distance from wire to pad in mm */
    float distance_l = a_static_l + b_static_l / signal_pad_r +
                       c_static_l / (POW2(signal_pad_r));
    float distance_r = a_static_r + b_static_r / signal_pad_l +
                       c_static_r / (POW2(signal_pad_l));

    /* Calculate distance from wire to board center */
    CALC_calc_distance_and_angle(distance_l, distance_r, &meas_data->distance,
    						&meas_data->angle);

    switch (phase) {
        case CALC_ONE_PHASE:
            /* Approximate current with averaging signal */
        	meas_data->current = (signal_coil_r + signal_coil_l) / 2 *
						meas_data->distance * a_magnetic_1;
            break;
        case CALC_THREE_PHASE:
            /* Approximate current with higher signal */
            if (signal_coil_r < signal_coil_l) {
            	meas_data->current = signal_coil_l * meas_data->distance * a_magnetic_3;
            } else {
            	meas_data->current = signal_coil_r * meas_data->distance * a_magnetic_3;
            }
            break;
    }

    if (20 < meas_data->current) {
    	meas_data->error = CALC_ERROR_OVERCURRENT;
	}
    if (cal_distance[2] < meas_data->distance) {
    	meas_data->error = CALC_ERROR_DISCONNECT;
	}
    if (90 < meas_data->angle) {
    	meas_data->angle = 90;
	}
    if (meas_data->angle < -90) {
    	meas_data->angle = -90;
	}
}


/** ***************************************************************************
 * @brief Accurate measurement
 * @param[out] *meas_data	Measurement data @see CALC_meas_data_t
 * @param[in]  phase		Select which phase mode for measurement
 *****************************************************************************/
void CALC_start_accurate_measurement(CALC_meas_data_t *meas_data, CALC_phase_item_t phase)
{
    float array_distance[ACCURATE_MEASUREMENT_LOOPS];
    float array_angle[ACCURATE_MEASUREMENT_LOOPS];
    float array_current[ACCURATE_MEASUREMENT_LOOPS];
    for (uint8_t i = 0; i < ACCURATE_MEASUREMENT_LOOPS; i++) {
        CALC_start_single_measurement(meas_data, phase);
        if (meas_data->error != CALC_ERROR_NONE) {
            break;
		}
        array_distance[i] = meas_data->distance;
        array_angle[i] = meas_data->angle;
        array_current[i] = meas_data->current;
    }

    if (meas_data->error == CALC_ERROR_NONE) {
        arm_mean_f32(array_distance, ACCURATE_MEASUREMENT_LOOPS, &meas_data->distance);
        arm_std_f32(array_distance, ACCURATE_MEASUREMENT_LOOPS, &meas_data->dist_sdev);
        arm_mean_f32(array_angle, ACCURATE_MEASUREMENT_LOOPS, &meas_data->angle);
        arm_std_f32(array_angle, ACCURATE_MEASUREMENT_LOOPS, &meas_data->angl_sdev);
        arm_mean_f32(array_current, ACCURATE_MEASUREMENT_LOOPS, &meas_data->current);
        arm_std_f32(array_current, ACCURATE_MEASUREMENT_LOOPS, &meas_data->curr_sdev);

        if (100 <= meas_data->curr_sdev) {
        	meas_data->error = CALC_ERROR_STANDARD_DEVIATION_TOO_HIGH;
		}
        if (100 <= meas_data->dist_sdev) {
        	meas_data->error = CALC_ERROR_STANDARD_DEVIATION_TOO_HIGH;
		}
        if (100 <= meas_data->angl_sdev) {
        	meas_data->error = CALC_ERROR_STANDARD_DEVIATION_TOO_HIGH;
		}
    }
}


/** ***************************************************************************
 * @brief Pad calibration
 * @param[in] state_pad_cali State of calibration
 *
 * To calibrate the pad (or distance) run this function multiple times
 * while changing the state of parameter state_pad_cali.
 *****************************************************************************/
void CALC_start_pad_calibration(CALC_cali_pad_step_t state_pad_cali)
{
    float signal_pad_l = 0;
    float signal_pad_r = 0;
    static float d1;
    static float s1_l;
    static float s1_r;
    static float d2;
    static float s2_l;
    static float s2_r;
    static float d3;
    static float s3_l;
    static float s3_r;

    uint8_t num_of_chan = MEAS_get_num_of_chan();
    uint8_t fft_len = MEAS_get_num_of_samples();

    if (state_pad_cali < CALC_CALI_P_FINISH) {
        for (uint8_t i = 0; i < ACCURATE_MEASUREMENT_LOOPS; i++) {
            uint32_t* ADC_samples = MEAS_start_meas();

            /* Split samples and convert to float */
            float ADC_samples_pad_r[fft_len];  // IN13 	PAD_RIGHT
            float ADC_samples_pad_l[fft_len];  // IN4  	PAD_LEFT
            for (uint8_t i = 0; i < fft_len; i++) {
                ADC_samples_pad_r[i] = (float)ADC_samples[num_of_chan * i];
                ADC_samples_pad_l[i] = (float)ADC_samples[num_of_chan * i + 1];
            }

            signal_pad_l += CALC_get_signalstrength(ADC_samples_pad_r, fft_len, 50);
            signal_pad_r += CALC_get_signalstrength(ADC_samples_pad_l, fft_len, 50);
        }
        signal_pad_l /= ACCURATE_MEASUREMENT_LOOPS;
        signal_pad_r /= ACCURATE_MEASUREMENT_LOOPS;
    }

    if (CALC_CALI_P_FIRST == state_pad_cali) {
        /* Calculate the wire to pad distance */
        d1 = sqrtf(POW2(cal_distance[CALC_CALI_P_FIRST - 1]) + POW2(D_P));
        s1_l = signal_pad_l;
        s1_r = signal_pad_r;
    } else if (CALC_CALI_P_SECOND == state_pad_cali) {
        /* Calculate the wire to pad distance */
        d2 = sqrtf(POW2(cal_distance[CALC_CALI_P_SECOND - 1]) + POW2(D_P));
        s2_l = signal_pad_l;
        s2_r = signal_pad_r;

    } else if (CALC_CALI_P_THIRD == state_pad_cali) {
        /* Calculate the wire to pad distance */
        d3 = sqrtf(POW2(cal_distance[CALC_CALI_P_THIRD - 1]) + POW2(D_P));
        s3_l = signal_pad_l;
        s3_r = signal_pad_r;

    } else if (CALC_CALI_P_FINISH == state_pad_cali) {
		/* Calculate coefficients for distance approximation */
        a_static_l = ((d1 * POW2(s1_l) * (s2_l - s3_l) -
                       d2 * (s1_l - s3_l) * POW2(s2_l) +
                       d3 * (s1_l - s2_l) * POW2(s3_l)) /
                      ((POW2(s1_l) - s1_l * (s2_l + s3_l) + s2_l * s3_l) *
                       (s2_l - s3_l)));
        b_static_l = ((-(d1 * POW2(s1_l) * (POW2(s2_l) - POW2(s3_l)) -
                         d2 * (POW2(s1_l) - POW2(s3_l)) * POW2(s2_l) +
                         d3 * (POW2(s1_l) - POW2(s2_l)) * POW2(s3_l))) /
                      ((POW2(s1_l) - s1_l * (s2_l + s3_l) + s2_l * s3_l) *
                       (s2_l - s3_l)));
        c_static_l = (((d1 * s1_l * (s2_l - s3_l) - d2 * (s1_l - s3_l) * s2_l +
                        d3 * (s1_l - s2_l) * s3_l) *
                       s1_l * s2_l * s3_l) /
                      ((POW2(s1_l) - s1_l * (s2_l + s3_l) + s2_l * s3_l) *
                       (s2_l - s3_l)));

        a_static_r = ((d1 * POW2(s1_r) * (s2_r - s3_r) -
                       d2 * (s1_r - s3_r) * POW2(s2_r) +
                       d3 * (s1_r - s2_r) * POW2(s3_r)) /
                      ((POW2(s1_r) - s1_r * (s2_r + s3_r) + s2_r * s3_r) *
                       (s2_r - s3_r)));
        b_static_r = ((-(d1 * POW2(s1_r) * (POW2(s2_r) - POW2(s3_r)) -
                         d2 * (POW2(s1_r) - POW2(s3_r)) * POW2(s2_r) +
                         d3 * (POW2(s1_r) - POW2(s2_r)) * POW2(s3_r))) /
                      ((POW2(s1_r) - s1_r * (s2_r + s3_r) + s2_r * s3_r) *
                       (s2_r - s3_r)));
        c_static_r = (((d1 * s1_r * (s2_r - s3_r) - d2 * (s1_r - s3_r) * s2_r +
                        d3 * (s1_r - s2_r) * s3_r) *
                       s1_r * s2_r * s3_r) /
                      ((POW2(s1_r) - s1_r * (s2_r + s3_r) + s2_r * s3_r) *
                       (s2_r - s3_r)));
    }
}


/** ***************************************************************************
 * @brief Coil calibration
 * @param[in] state_phase Select which phase mode for measurement
 * @param[in] state_coil_cali State of calibration
 *
 * To calibrate the coil (or current) run this function multiple times
 * while changing the state of parameter state_coil_cali.
 *****************************************************************************/
void CALC_start_coil_calibration(CALC_phase_item_t state_phase,
                                 CALC_cali_coil_step_t state_coil_cali)
{
    static CALC_meas_data_t meas_data;
    static float signal;

    if (CALC_CALI_C_FIRST == state_coil_cali) {
        CALC_start_accurate_measurement(&meas_data, state_phase);
        if (state_phase == CALC_ONE_PHASE) {
            signal = meas_data.current / (a_magnetic_1 * meas_data.distance);
        } else if (state_phase == CALC_THREE_PHASE) {
        	signal = meas_data.current / (a_magnetic_3 * meas_data.distance);
        }

    } else if (CALC_CALI_C_FINISH == state_coil_cali) {
        if (state_phase == CALC_ONE_PHASE) {
            a_magnetic_1 =
                cal_current[CALC_CALI_C_FIRST - 1] / (signal * meas_data.distance);
        } else if (state_phase == CALC_THREE_PHASE) {
            a_magnetic_3 =
                cal_current[CALC_CALI_C_FIRST - 1] / (signal * meas_data.distance);
        }
    }
}


/** ***************************************************************************
 * @brief Get distances for measurements
 * @return Array of distances
 *****************************************************************************/
float *CALC_get_act_dist(void) {
    return cal_distance;
}


/** ***************************************************************************
 * @brief Get current for measurements
 * @return Array of current
 *****************************************************************************/
float *CALC_get_act_curr(void) {
    return cal_current;
}

