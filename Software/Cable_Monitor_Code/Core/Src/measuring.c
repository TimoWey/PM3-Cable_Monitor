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
#include <stdio.h>
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"
#include "stm32f4xx.h"

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
static uint32_t ADC_samples[INPUT_COUNT *
                            ADC_NUMS];  ///< ADC values of max. 4 input channels

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
static void MEAS_Buffer_reset(uint8_t channels, uint32_t* buffer) {
    /* Clear buffer and flag */
    for (uint32_t i = 0; i < ADC_NUMS * channels; i++) {
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
 * @n The inputs used are ADC3_IN4 = GPIO PF6 (Pad Left), ADC3_IN13 = GPIO PC3
 *(Pad Right), ADC_IN6 = GPIO PF8 (HS-Left), ADC3_IN11 = GPIO PC1 (HS-Right)
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
    while (DMA2_Stream1->CR & DMA_SxCR_EN) {
        ;
    }                                 // Wait for DMA to finish
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
void MEAS_ADC3_scan_start(void) {
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
void DMA2_Stream1_IRQHandler(void) {
    if (DMA2->LISR & DMA_LISR_TCIF1) {  // Stream1 transfer compl. interrupt f.
        NVIC_DisableIRQ(
            DMA2_Stream1_IRQn);  // Disable DMA interrupt in the NVIC
        NVIC_ClearPendingIRQ(DMA2_Stream1_IRQn);  // Clear pending DMA interrupt
        DMA2_Stream1->CR &= ~DMA_SxCR_EN;         // Disable the DMA
        while (DMA2_Stream1->CR & DMA_SxCR_EN) {
            ;
        }  // Wait for DMA to finish
        DMA2->LIFCR |=
            DMA_LIFCR_CTCIF1;        // Clear transfer complete interrupt fl.
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
uint32_t* MEAS_start_measure(void) {
    MEAS_Buffer_reset(INPUT_COUNT, ADC_samples);
    MEAS_ADC3_scan_init();
    MEAS_ADC3_scan_start();
    while (!MEAS_data_ready)
        ;  // Wait for data
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

/**
 * @brief Initializes the MEAS timer.
 *
 * This function enables the clock for timer 3, sets the prescaler to 16000,
 * sets the auto reload register to 100, enables the update interrupt,
 * enables timer 3, and enables the timer 3 interrupt.
 * This timer is used to trigger the data output to the display every 800ms.
 */
void OUTPUT_MEAS_timer_init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;  // enable clock for timer 3
    TIM3->PSC = 16000 - 1;               // set prescaler to 16000
    TIM3->ARR = 800 - 1;                 // set auto reload register to 800
    TIM3->DIER |= TIM_DIER_UIE;          // enable update interrupt
    TIM3->CR1 |= TIM_CR1_CEN;            // enable timer 3
    NVIC_SetPriority(TIM3_IRQn, 3);
    NVIC_EnableIRQ(TIM3_IRQn);  // enable timer 3 interrupt
}



/* uint32_t frequency_calculation(uint8_t Channel, uint32_t* Samples) {
	uint32_t first_peak_index = 0;
	uint32_t last_peak_index = 0;
	uint32_t peak_count = 0;
	for (uint32_t i = 1; i < ADC_NUMS - 1; i++) {
		if (Samples[4 * i + Channel] > Samples[4 * (i - 1) + Channel] &&
			Samples[4 * i + Channel] > Samples[4 * (i + 1) + Channel]) {
			if (last_peak_index != 0) {
				peak_count++;
			} else {
				first_peak_index = i;
			}
			last_peak_index = i;
		}
	}

	float frequency = 0;
	if (peak_count > 0) {
		float average_period =
			(float)(last_peak_index - first_peak_index) / peak_count;
		frequency = ADC_FS / average_period;
	}
	return frequency;
} */

/** ***************************************************************************
 * @brief Draw buffer data as curves
 *
 * and write the first two samples as numbers.
 * @n After drawing, the buffer is cleared to get ready for the next run.
 * @note Drawing outside of the display crashes the system!
 * @todo Create new .h and .c files for calculating and displaying
 * of signals and results.
 * The code of this function was put into the same file for debugging purposes
 * and should be moved to a separate file in the final version
 * because displaying is not related to measuring.
 *****************************************************************************/

void MEAS_show_data(void) {
    const uint8_t ADC_RES = 12;
    // Define Samples variable and start measurement
    uint32_t* Samples = MEAS_start_measure();
    /* Calculate the factor to scale the values to the display */
    const uint32_t Y_OFFSET = 100;
    const uint32_t X_SIZE = 240;
    const uint32_t f = (1 << ADC_RES) / Y_OFFSET + 1;  // Scaling factor
    uint32_t data;
    uint32_t data_last;
    /* Clear the display */

    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    BSP_LCD_FillRect(0, 0, X_SIZE, Y_OFFSET + 1);
    /* Write first 4 samples as numbers */

    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font12);
    BSP_LCD_DisplayStringAt(0, 80, (uint8_t*)"ADC Resolution: 12 bit",
                            CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Peak Values and frequency", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 120, (uint8_t*)"of Channels 1 to 4:", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, 260, (uint8_t*)"(without VGND -> peak - 2048)",
                            CENTER_MODE);
    BSP_LCD_SetFont(&Font20);
    char text[32];
	// Calculate the frequency of channel 1
	static float frequency = 0;
	frequency = calculate_main_frequency(1, Samples, INPUT_COUNT, ADC_NUMS, ADC_FS);
    //uint32_t frequency = frequency_calculation(0, Samples);
    // Calculate the peak value of channel 1
    uint32_t peak = 0;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        if (Samples[4 * i] > peak) {
            peak = Samples[4 * i];
        }
    }
    peak -= 2048;
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
    snprintf(text, 40, "C1:%4d f:%3d HZ", (int)(peak), (int)(frequency));
    // snprintf(text, 15, "C1 %4d", (int)(Samples[0]));
    BSP_LCD_DisplayStringAt(0, 140, (uint8_t*)text, LEFT_MODE);
	// Calculate the frequency of channel 2
	frequency = calculate_main_frequency(2, Samples, INPUT_COUNT, ADC_NUMS, ADC_FS);
    //frequency = frequency_calculation(1, Samples);
    // Calculate the peak value of channel 2
    peak = 0;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        if (Samples[4 * i + 1] > peak) {
            peak = Samples[4 * i + 1];
        }
    }
    peak -= 2048;
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    snprintf(text, 40, "C2:%4d f:%3d HZ", (int)(peak), (int)(frequency));
    // snprintf(text, 15, "C2 %4d", (int)(Samples[1]));
    BSP_LCD_DisplayStringAt(0, 170, (uint8_t*)text, LEFT_MODE);
	// Calculate the frequency of channel 3
	frequency = calculate_main_frequency(3, Samples, INPUT_COUNT, ADC_NUMS, ADC_FS);
    //frequency = frequency_calculation(2, Samples);
    // Calculate the peak value of channel 3
    peak = 0;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        if (Samples[4 * i + 2] > peak) {
            peak = Samples[4 * i + 2];
        }
    }
    peak -= 2048;
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    snprintf(text, 40, "C3:%4d f:%3d HZ ", (int)(peak), (int)(frequency));
    // snprintf(text, 15, "C3 %4d", (int)(Samples[2]));
    BSP_LCD_DisplayStringAt(0, 200, (uint8_t*)text, LEFT_MODE);
	// Calculate the frequency of channel 4
	frequency = calculate_main_frequency(4, Samples, INPUT_COUNT, ADC_NUMS, ADC_FS);
    //frequency = frequency_calculation(3, Samples);
    // Calculate the peak value of channel 4
    peak = 0;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        if (Samples[4 * i + 3] > peak) {
            peak = Samples[4 * i + 3];
        }
    }
    peak -= 2048;
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    snprintf(text, 40, "C4:%4d f:%3d HZ", (int)(peak), (float)(frequency));
    // snprintf(text, 15, "C4 %4d", (int)(Samples[3]));
    BSP_LCD_DisplayStringAt(0, 230, (uint8_t*)text, LEFT_MODE);
    /* Draw the  values of input channel 1 as a curve */
    BSP_LCD_SetTextColor(LCD_COLOR_CYAN);
    data = Samples[0] / f;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        data_last = data;
        data = (Samples[4 * i]) / f;
        if (data > Y_OFFSET) {
            data = Y_OFFSET;
        }  // Limit value, prevent crash
        BSP_LCD_DrawLine(4 * (i - 1), Y_OFFSET - data_last, 4 * i,
                         Y_OFFSET - data);
    }
    /* Draw the  values of input channel 2 as a curve */
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    data = Samples[1] / f;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        data_last = data;
        data = (Samples[4 * i + 1]) / f;
        if (data > Y_OFFSET) {
            data = Y_OFFSET;
        }  // Limit value, prevent crash
        BSP_LCD_DrawLine(4 * (i - 1), Y_OFFSET - data_last, 4 * i,
                         Y_OFFSET - data);
    }
    /* Draw the  values of input channel 3 as a curve */
    BSP_LCD_SetTextColor(LCD_COLOR_YELLOW);
    data = Samples[2] / f;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        data_last = data;
        data = (Samples[4 * i + 2]) / f;
        if (data > Y_OFFSET) {
            data = Y_OFFSET;
        }  // Limit value, prevent crash
        BSP_LCD_DrawLine(4 * (i - 1), Y_OFFSET - data_last, 4 * i,
                         Y_OFFSET - data);
    }
    /* Draw the  values of input channel 4 as a curve */
    BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
    data = Samples[3] / f;
    for (uint32_t i = 0; i < ADC_NUMS; i++) {
        data_last = data;
        data = (Samples[4 * i + 3]) / f;
        if (data > Y_OFFSET) {
            data = Y_OFFSET;
        }  // Limit value, prevent crash
        BSP_LCD_DrawLine(4 * (i - 1), Y_OFFSET - data_last, 4 * i,
                         Y_OFFSET - data);
    }
}

/**
 * @brief Interrupt handler for TIM3.
 *
 * This function is called when the update interrupt flag of TIM3 is set.
 * It clears the update interrupt flag and calls the MEAS_show_data() function
 * to output data to the display.
 */
void TIM3_IRQHandler(void) {
    if (TIM3->SR & TIM_SR_UIF) {  // check if update interrupt flag is set
        TIM3->SR &= ~TIM_SR_UIF;  // clear update interrupt flag
        MEAS_show_data();         // output data to display
    }
}
