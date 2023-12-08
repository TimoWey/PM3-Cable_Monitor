/** ***************************************************************************
 * @file
 * @brief See measuring.c
 *
 * Prefixes MEAS, ADC, DAC
 *
 *****************************************************************************/

#ifndef MEASURING_H_
#define MEASURING_H_


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdbool.h>


/******************************************************************************
 * Defines
 *****************************************************************************/
extern bool MEAS_data_ready;
extern uint32_t MEAS_input_count;


/******************************************************************************
 * Functions
 *****************************************************************************/
void MEAS_GPIO_analog_init(void);
void MEAS_timer_init(void);

void ADC_reset(void);
uint8_t MEAS_get_num_of_chan(void);
uint8_t MEAS_get_num_of_samples(void);
uint16_t MEAS_get_samp_freq(void);
uint32_t *MEAS_start_measure(void);
void MEAS_show_data(void);


#endif
