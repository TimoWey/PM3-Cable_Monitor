/** ***************************************************************************
 * @file
 * @brief Measuring voltages with the ADC(s) in different configurations
 *
 *
 * Demonstrates different ADC (Analog to Digital Converter) modes
 * ==============================================================
 *
 * - ADC in single conversion mode
 * - ADC triggered by a timer and with interrupt after end of conversion
 * - ADC combined with DMA (Direct Memory Access) to fill a buffer
 * - Dual mode = simultaneous sampling of two inputs by two ADCs
 * - Scan mode = sequential sampling of two inputs by one ADC
 * - Simple DAC output is demonstrated as well
 * - Analog mode configuration for GPIOs
 * - Display recorded data on the graphics display
 *
 * Peripherals @ref HowTo
 *
 * @image html demo_screenshot_board.jpg
 *
 *
 * HW used for the demonstrations
 * ==============================
 * A simple HW was used for testing the code.
 * It is connected to the pins marked in red in the above image.
 *
 * @image html demo_board_schematic.png
 *
 * Of course the code runs also without this HW.
 * Simply connect a signal or waveform generator to the input(s).
 *
 *
 * @anchor HowTo
 * How to Configure the Peripherals: ADC, TIMER and DMA
 * ====================================================
 *
 * All the peripherals are accessed by writing to or reading from registers.
 * From the programmer’s point of view this is done exactly as
 * writing or reading the value of a variable.
 * @n Writing to a register configures the HW of the associated peripheral
 * to do what is required.
 * @n Reading from a registers gets status and data from the HW peripheral.
 *
 * The information on which bits have to be set to get a specific behavior
 * is documented in the <b>reference manual</b> of the mikrocontroller.
 *
 *
 * ----------------------------------------------------------------------------
 * @author Alejandro Horvat, horvaale@zhaw.ch
 * @date 17.06.2021
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "measuring.h"
#include "calculation.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define ADC_NUMS 64         ///< Number of samples
#define ADC_FS 640          ///< Sampling freq. => 12 samples for a 50Hz period
#define TIM_CLOCK 84000000  ///< APB1 timer clock frequency
#define TIM_TOP 9           ///< Timer top value
#define TIM_PRESCALE \
    (TIM_CLOCK / ADC_FS / (TIM_TOP + 1) - 1)  ///< Clock prescaler
#define INPUT_COUNT 4                         ///< Number of input channels

/******************************************************************************
 * Variables
 *****************************************************************************/
bool MEAS_data_ready = false;          ///< New data is ready
static uint32_t ADC_sample_count = 0;  ///< Index for buffer
///< ADC values of max. 4 input channels
static uint32_t ADC_samples[INPUT_COUNT * ADC_NUMS];

/******************************************************************************
 * Functions
 *****************************************************************************/

/** ***************************************************************************
 * @brief Configure GPIOs in analog mode.
 *
 * @note The input number for the ADCs is not equal to the GPIO pin number!
 * - ADC3_IN4 = GPIO PF6 (Pad left)
 * - ADC123_IN13 = GPIO PC3 (Pad right)
 * - ADC3_IN6 = GPIO PF8 (Hall sensor Left)
 * - ADC123_IN11 = GPIO PC1 (Hall sensor Right)
 *****************************************************************************/
void MEAS_GPIO_analog_init(void) {
    __HAL_RCC_GPIOF_CLK_ENABLE();  // Enable Clock for GPIO port F
    GPIOF->MODER |= (3UL << GPIO_MODER_MODER6_Pos);  // Analog PF6 = ADC3_IN4
    GPIOF->MODER |= (3UL << GPIO_MODER_MODER8_Pos);  // Analog PF8 = ADC3_IN6
    __HAL_RCC_GPIOC_CLK_ENABLE();  // Enable Clock for GPIO port C
    GPIOC->MODER |= (3UL << GPIO_MODER_MODER3_Pos);  // Analog PC3 = ADC3_IN13
    GPIOC->MODER |= (3UL << GPIO_MODER_MODER1_Pos);  // Analog PC1 = ADC3_IN11
}

/** ***************************************************************************
 * @brief Resets the ADCs and the timer
 *
 * to make sure the different demos do not interfere.
 *****************************************************************************/
void MEAS_ADC_reset(void) {
    RCC->APB2RSTR |= RCC_APB2RSTR_ADCRST;   // Reset ADCs
    RCC->APB2RSTR &= ~RCC_APB2RSTR_ADCRST;  // Release reset of ADCs
    TIM2->CR1 &= ~TIM_CR1_CEN;              // Disable timer
}

/** ***************************************************************************
 * @brief Resets the buffer and the flag (data ready for new measurement)
 * @param[in] channels	input channels
 * @param[in] buffer	buffer pointer
 *****************************************************************************/
static void MEAS_Buffer_reset(uint8_t channels, uint32_t* buffer)
{
    /* Clear buffer and flag */
    for (uint32_t i = 0; i < ADC_NUMS * channels; i++)
    {
        buffer[i] = 0;
    }
}

/** ***************************************************************************
 * @brief Configure the timer to trigger the ADC(s)
 *
 * @note For debugging purposes the timer interrupt might be useful.
 *****************************************************************************/
void MEAS_timer_init(void) {
    __HAL_RCC_TIM2_CLK_ENABLE();  // Enable Clock for TIM2
    TIM2->PSC = TIM_PRESCALE;     // Prescaler for clock freq. = 1MHz
    TIM2->ARR = TIM_TOP;          // Auto reload = counter top value
    TIM2->CR2 |= TIM_CR2_MMS_1;   // TRGO on update
}

/** ***************************************************************************
 * @brief Initialize ADC, timer and DMA for sequential acquisition = scan mode
 *
 * Uses ADC2 and DMA2_Stream1 channel2
 * @n The ADC2 trigger is set to TIM2 TRGO event
 * @n At each trigger both inputs are converted sequentially
 * and transfered to memory by the DMA.
 * @n As each conversion triggers the DMA, the number of transfers is doubled.
 * @n The DMA triggers the transfer complete interrupt when all data is ready.
 * @n The inputs used are ADC3_IN4 = GPIO PF6 (Pad Right), ADC3_IN13 = GPIO PC3
 *(Pad Left), ADC_IN6 = GPIO PF8 (HS-Right), ADC3_IN11 = GPIO PC1 (HS-Left)
 *****************************************************************************/
void MEAS_ADC3_scan_init(void) {
    __HAL_RCC_ADC3_CLK_ENABLE();               // Enable Clock for ADC3
    ADC3->SQR1 |= (3UL << ADC_SQR1_L_Pos);     // Convert 4 inputs (4-1)
    ADC3->SQR3 |= (4UL << ADC_SQR3_SQ1_Pos);   // Input 4 = first conversion
    ADC3->SQR3 |= (13UL << ADC_SQR3_SQ2_Pos);  // Input 13 = second conversion
    ADC3->SQR3 |= (6UL << ADC_SQR3_SQ3_Pos);   // Input 6 = third conversion
    ADC3->SQR3 |= (11UL << ADC_SQR3_SQ4_Pos);  // Input 11 = fourth conversion
    ADC3->CR1 |= ADC_CR1_SCAN;                 // Enable scan mode
    ADC3->CR2 |= (1UL << ADC_CR2_EXTEN_Pos);   // En. ext. trigger on rising e.
    ADC3->CR2 |= (6UL << ADC_CR2_EXTSEL_Pos);  // Timer 2 TRGO event
    ADC3->CR2 |= ADC_CR2_DMA;                  // Enable DMA mode
    __HAL_RCC_DMA2_CLK_ENABLE();               // Enable Clock for DMA2
    DMA2_Stream1->CR &= ~DMA_SxCR_EN;          // Disable the DMA stream 1
    while (DMA2_Stream1->CR & DMA_SxCR_EN){};  // Wait for DMA to finish
    DMA2->LIFCR |= DMA_LIFCR_CTCIF1;  // Clear transfer complete interrupt fl.
    DMA2_Stream1->CR |= (2UL << DMA_SxCR_CHSEL_Pos);  // Select channel 2
    DMA2_Stream1->CR |= DMA_SxCR_PL_1;                // Priority high
    DMA2_Stream1->CR |= DMA_SxCR_MSIZE_1;  // Memory data size = 32 bit
    DMA2_Stream1->CR |= DMA_SxCR_PSIZE_1;  // Peripheral data size = 32 bit
    DMA2_Stream1->CR |= DMA_SxCR_MINC;     // Increment memory address pointer
    DMA2_Stream1->CR |= DMA_SxCR_TCIE;     // Transfer complete interrupt enable
    DMA2_Stream1->NDTR =
        INPUT_COUNT * ADC_NUMS;  // Number of data items to transfer
    DMA2_Stream1->PAR = (uint32_t)&ADC3->DR;     // Peripheral register address
    DMA2_Stream1->M0AR = (uint32_t)ADC_samples;  // Buffer memory loc. address
}

/** ***************************************************************************
 * @brief Start DMA, ADC and timer
 *
 *****************************************************************************/
void MEAS_ADC3_scan_start(void)
{
    DMA2_Stream1->CR |= DMA_SxCR_EN;          // Enable DMA
    NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);  // Clear pending DMA interrupt
    NVIC_EnableIRQ(DMA2_Stream1_IRQn);  // Enable DMA interrupt in the NVIC
    ADC3->CR2 |= ADC_CR2_ADON;          // Enable ADC3
    TIM2->CR1 |= TIM_CR1_CEN;           // Enable timer
}

/** ***************************************************************************
 * @brief Interrupt handler for DMA2 Stream1
 *
 * The samples from the ADC3 have been transfered to memory by the DMA2 Stream1
 * and are ready for processing.
 *****************************************************************************/
void DMA2_Stream1_IRQHandler(void)
{
    static int debug = 0;
    debug++;
    //HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);

	if (DMA2->LISR & DMA_LISR_TCIF1) // Stream1 transfer compl. interrupt f.
    {
        // Disable DMA interrupt in the NVIC
    	NVIC_DisableIRQ(DMA2_Stream1_IRQn);
        NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);  // clr pending DMA interrupt
        DMA2_Stream1->CR &= ~DMA_SxCR_EN;         // Disable the DMA
        while (DMA2_Stream1->CR & DMA_SxCR_EN)	  // Wait for DMA to finish
        {
            ;
        }
        DMA2->LIFCR |= DMA_LIFCR_CTCIF1;// clr transfer complete interrupt fl.
        TIM2->CR1 &= ~TIM_CR1_CEN;   // Disable timer
        ADC3->CR2 &= ~ADC_CR2_ADON;  // Disable ADC3
        ADC3->CR2 &= ~ADC_CR2_DMA;   // Disable DMA mode

        // copy data from DMA buffer to ADC_samples
        MEAS_ADC_reset();
        MEAS_data_ready = true;
    }
}

/** ***************************************************************************
 * Measurement functions
 *****************************************************************************/
/** ***************************************************************************
 * @brief Start the measurement
 * @return ADC samples pointer
 *
 * @note The result is stored alternated e.g. every 4th is together.
 *****************************************************************************/
// Start the measurement procedure
uint32_t* MEAS_start_measure(void)
{
    //works
	MEAS_Buffer_reset(INPUT_COUNT, ADC_samples);

    //
	MEAS_ADC3_scan_init();

	//
    MEAS_ADC3_scan_start();

    static int timeout = 0;
    while ((!MEAS_data_ready) & (timeout > 99999))
    {
    	// Wait for data
    	timeout++;
    }
    MEAS_data_ready = false;
    timeout=0;

//    HAL_Delay(100);

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
