/** ***************************************************************************
 * @file
 * @brief See calculation.c
 *
 * Prefix CALC
 *
 *****************************************************************************/

#ifndef CALC_H_
#define CALC_H_


/******************************************************************************
 * Includes
 *****************************************************************************/


/******************************************************************************
 * Defines
 *****************************************************************************/


/******************************************************************************
 * Types
 *****************************************************************************/
/** Enumeration of possible measurement error items */
typedef enum {
	CALC_ERROR_DISCONNECT = 0,				///< wire too far away
	CALC_ERROR_OVERCURRENT,					///< overcurrent
	CALC_ERROR_STANDARD_DEVIATION_TOO_HIGH,	///< standard deviation too high
	/* add new error item */
	CALC_ERROR_NONE		/* must be the last entry */	///< none error
} CALC_error_item_t;


/** Enumeration of possible phase items */
typedef enum {
	CALC_ONE_PHASE = 0,	///< one phase
	CALC_THREE_PHASE	///< three phase
} CALC_phase_item_t;


/** Enumeration of possible pad calculation points */
typedef enum {
	CALC_CALI_P_START = 0,	///< start distance calibration
	CALC_CALI_P_FIRST,		///< first distance calibration
	CALC_CALI_P_SECOND,		///< second distance calibration
	CALC_CALI_P_THIRD,		///< third distance calibration
	/* new pad cali point */
	CALC_CALI_P_FINISH,		///< finish distance calibration
	CALC_CALI_P_ABOARD,		///< aboard distance calibration
	CALC_CALI_P_END			///< end distance calibration
} CALC_cali_pad_step_t;


/** Enumeration of possible coil calculation points */
typedef enum {
	CALC_CALI_C_START = 0,	///< start current calibration
	CALC_CALI_C_FIRST,		///< first current calibration
	/* new coil cali point */
	CALC_CALI_C_FINISH,		///< finish current calibration
	CALC_CALI_C_ABOARD,		///< aboard current calibration
	CALC_CALI_C_END			///< end current calibration
} CALC_cali_coil_step_t;


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
 * Functions
 *****************************************************************************/
float calculate_main_frequency(uint8_t Channel, float* samples, uint8_t num_channels, uint32_t buffer_size, uint32_t sampling_freq);


#endif	/* CALC_H_ */

