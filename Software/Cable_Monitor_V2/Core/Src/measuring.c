/** ***************************************************************************
 * @file
 * @brief Measuring voltages with the ADC's in different configurations
 *
 * Initializes the GPIO for the ADC's.
 * @n Implements the interrupt handler for the measurements
 * and prepares the measurement data.
 *
 * ----------------------------------------------------------------------------
 * @author  Flavio Felder, feldefla@students.zhaw.ch
 * @date	12.28.2021
 *****************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdbool.h>
#include "stm32f4xx.h"

#include "measuring.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define ADC_NUMS		64 ///< Number of samples @see get_signalstrength()
#define ADC_FS			640 ///< Sampling freq. @see get_signalstrength()
#define INPUT_COUNT		4 ///< 4 input channels
#define TIM_CLOCK		84000000 ///< APB1 timer clock frequency
#define TIM_TOP			9 ///< Timer top value
#define TIM_PRESCALE	(TIM_CLOCK/ADC_FS/(TIM_TOP+1)-1) ///< Clock prescaler


/******************************************************************************
 * Variables
 *****************************************************************************/
static bool MEAS_data_ready = false; ///< New data is ready
static uint32_t ADC_samples[INPUT_COUNT*ADC_NUMS];
			///< ADC values of max. 4 input channels


/******************************************************************************
 * Functions
 *****************************************************************************/
static void MEAS_Buffer_reset(uint8_t channels, uint32_t *buffer);
static void MEAS_ADC_reset(void);
static void MEAS_ADC3_IN13_IN4_IN11_IN6_scan_init(void);
static void MEAS_ADC3_scan_start(void);


/** ***************************************************************************
 * @brief Resets the buffer
 * @param[in] channels	input channels
 * @param[in] buffer	buffer pointer
 *****************************************************************************/
static void MEAS_Buffer_reset(uint8_t channels, uint32_t *buffer) {
	/* Clear buffer and flag */
	for (uint16_t i = 0; i < ADC_NUMS*channels; i++){
		buffer[i] = 0;
	}
}


/** ***************************************************************************
 * @brief Resets the ADCs and the timer
 *
 * Reset them to make sure the different functions do not interfere.
 *****************************************************************************/
static void MEAS_ADC_reset(void) {
	RCC->APB2RSTR |= RCC_APB2RSTR_ADCRST;	// Reset ADCs
	RCC->APB2RSTR &= ~RCC_APB2RSTR_ADCRST;	// Release reset of ADCs
	TIM2->CR1 &= ~TIM_CR1_CEN;				// Disable timer
}


/** ***************************************************************************
 * @brief Initialize ADC, timer and DMA for sequential acquisition = scan mode
 *
 * Uses ADC3 and DMA2_Stream1 channel2
 * @n The ADC3 trigger is set to TIM2 TRGO event
 * @n At each trigger all inputs are converted sequentially
 * and transfered to memory by the DMA.
 * @n The DMA triggers the transfer complete interrupt when all data is ready.
 * @n The inputs used are ADC123_IN13 = GPIO PC3, ADC3_IN4 = GPIO PF6,
 * ADC123_IN11 = GPIO PC1 and ADC3_IN6 = GPIO PF8.
 *****************************************************************************/
static void MEAS_ADC3_IN13_IN4_IN11_IN6_scan_init(void)
{
	__HAL_RCC_ADC3_CLK_ENABLE(); // Enable Clock for ADC3
	ADC3->SQR1 |= (ADC_SQR1_L_1 | ADC_SQR1_L_0); // Convert 4 inputs
	ADC3->SQR3 |= (13UL << ADC_SQR3_SQ1_Pos); // Input 13 = first conversion
	ADC3->SQR3 |= (4UL << ADC_SQR3_SQ2_Pos); // Input 4 = second conversion
	ADC3->SQR3 |= (11UL << ADC_SQR3_SQ3_Pos); // Input 11 = first conversion
	ADC3->SQR3 |= (6UL << ADC_SQR3_SQ4_Pos); // Input 6 = second conversion
	ADC3->CR1 |= ADC_CR1_SCAN; // Enable scan mode
	ADC3->CR2 |= (1UL << ADC_CR2_EXTEN_Pos); // En. ext. trigger on rising e.
	ADC3->CR2 |= (6UL << ADC_CR2_EXTSEL_Pos); // Timer 2 TRGO event
	ADC3->CR2 |= ADC_CR2_DMA; // Enable DMA mode
	__HAL_RCC_DMA2_CLK_ENABLE(); // Enable Clock for DMA2
	DMA2_Stream1->CR &= ~DMA_SxCR_EN; // Disable the DMA stream 1
	while (DMA2_Stream1->CR & DMA_SxCR_EN) { ; } // Wait for DMA to finish
	DMA2->LIFCR |= DMA_LIFCR_CTCIF1; // Clear transfer complete interrupt fl.
	DMA2_Stream1->CR |= (2UL << DMA_SxCR_CHSEL_Pos); // Select channel 2
	DMA2_Stream1->CR |= DMA_SxCR_PL_1; // Priority high
	DMA2_Stream1->CR |= DMA_SxCR_MSIZE_1; // Memory data size = 32 bit
	DMA2_Stream1->CR |= DMA_SxCR_PSIZE_1; // Peripheral data size = 32 bit
	DMA2_Stream1->CR |= DMA_SxCR_MINC; // Increment memory address pointer
	DMA2_Stream1->CR |= DMA_SxCR_TCIE; // Transfer complete interrupt enable
	DMA2_Stream1->NDTR = INPUT_COUNT*ADC_NUMS; // Number of data items to transfer
	DMA2_Stream1->PAR = (uint32_t)&ADC3->DR; // Peripheral register address
	DMA2_Stream1->M0AR = (uint32_t)ADC_samples; // Buffer memory loc. address
}


/** ***************************************************************************
 * @brief Start DMA, ADC and timer
 *
 *****************************************************************************/
static void MEAS_ADC3_scan_start(void)
{
	DMA2_Stream1->CR |= DMA_SxCR_EN; // Enable DMA
	NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn); // Clear pending DMA interrupt
	NVIC_EnableIRQ(DMA2_Stream1_IRQn); // Enable DMA interrupt in the NVIC
	ADC3->CR2 |= ADC_CR2_ADON; // Enable ADC3
	TIM2->CR1 |= TIM_CR1_CEN; // Enable timer
}


/** ***************************************************************************
 * @brief Configure GPIOs in analog mode.
 *
 * @note The input number for the ADCs is not equal to the GPIO pin number!
 * - ADC3_IN4 = GPIO PF6
 * - ADC123_IN13 = GPIO PC3
 *****************************************************************************/
void MEAS_GPIO_analog_init(void)
{
	__HAL_RCC_GPIOF_CLK_ENABLE();		// Enable Clock for GPIO port F
	GPIOF->MODER |= (GPIO_MODER_MODER6_Msk);// Analog mode for PF6 = ADC3_IN4
	__HAL_RCC_GPIOC_CLK_ENABLE();		// Enable Clock for GPIO port C
	GPIOC->MODER |= (GPIO_MODER_MODER3_Msk);// Analog mode for PC3 = ADC123_IN13
}


/** ***************************************************************************
 * @brief Configure the timer to trigger the ADC's
 *
 *****************************************************************************/
void MEAS_timer_init(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();		// Enable Clock for TIM2
	TIM2->PSC = TIM_PRESCALE;			// Prescaler for clock freq. = 1MHz
	TIM2->ARR = TIM_TOP;				// Auto reload = counter top value
	TIM2->CR2 |= TIM_CR2_MMS_1; 		// TRGO on update
}


/** ***************************************************************************
 * @brief Interrupt handler for DMA2 stream 1
 *
 * The samples from the ADC3 have been transfered to memory by the DMA2 Stream1
 * and are ready for processing.
 *****************************************************************************/
void DMA2_Stream1_IRQHandler(void)
{
	if (DMA2->LISR & DMA_LISR_TCIF1) {	// Stream1 transfer compl. interrupt f.
		NVIC_DisableIRQ(DMA2_Stream1_IRQn);	// Disable DMA interrupt in the NVIC
		NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);// Clear pending DMA interrupt
		DMA2_Stream1->CR &= ~DMA_SxCR_EN;	// Disable the DMA
		while (DMA2_Stream1->CR & DMA_SxCR_EN) { ; }	// Wait for DMA to finish
		DMA2->LIFCR |= DMA_LIFCR_CTCIF1;// Clear transfer complete interrupt fl.
		TIM2->CR1 &= ~TIM_CR1_CEN;		// Disable timer
		ADC3->CR2 &= ~ADC_CR2_ADON;		// Disable ADC3
		ADC3->CR2 &= ~ADC_CR2_DMA;		// Disable DMA mode
		MEAS_ADC_reset();
		MEAS_data_ready = true;
	}
}


/** ***************************************************************************
 * @brief Start the measurement
 * @return ADC samples pointer
 * 
 * @note The result is stored alternated e.g. every 4th is together.
 *****************************************************************************/
uint32_t *MEAS_start_meas(void)
{
	MEAS_Buffer_reset(INPUT_COUNT, ADC_samples);
	MEAS_ADC3_IN13_IN4_IN11_IN6_scan_init();
	MEAS_ADC3_scan_start();
	while(!MEAS_data_ready);
	MEAS_data_ready = false;

	return ADC_samples;
}


/** ***************************************************************************
 * @brief Get the number of channels
 * @return Number of channels
 *****************************************************************************/
uint8_t MEAS_get_num_of_chan(void)
{
	return INPUT_COUNT;
}


/** ***************************************************************************
 * @brief Get the number of samples
 * @return Number of samples
 *****************************************************************************/
uint8_t MEAS_get_num_of_samples(void)
{
	return ADC_NUMS;
}


/** ***************************************************************************
 * @brief Get the sampling frequency
 * @return Sampling frequency
 *****************************************************************************/
uint16_t MEAS_get_samp_freq(void)
{
	return ADC_FS;
}


/** ***************************************************************************
 * @brief Get the samples
 * @return ADC samples pointer
 *****************************************************************************/
uint32_t *MEAS_get_samples(void)
{
	return ADC_samples;
}

