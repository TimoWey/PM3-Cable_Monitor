/** ***************************************************************************
 * @file
 * @brief See measuring.c
 *
 * Prefixes MEAS, ADC, DAC
 *
 *****************************************************************************/

#ifndef MEAS_H_
#define MEAS_H_


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdbool.h>


/******************************************************************************
 * Defines
 *****************************************************************************/
extern bool MEAS_data_ready;
extern uint32_t MEAS_input_count;
extern bool DAC_active;


/******************************************************************************
 * Functions
 *****************************************************************************/
void MEAS_GPIO_analog_init(void);
void ADC_reset(void);
static void MEAS_Buffer_reset(uint8_t channels, uint32_t *buffer);
void MEAS_timer_init(void);
void ADC3_scan_init(void);
void ADC3_scan_start(void);
void ADC_IRQHandler(void);
void DMA2_Stream1_IRQHandler(void);
uint32_t MEAS_start_measure(void);
void MEAS_show_data(void);

#endif
