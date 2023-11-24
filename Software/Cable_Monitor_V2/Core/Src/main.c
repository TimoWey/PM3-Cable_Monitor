/** ***************************************************************************
 * @file
 * @brief Sets up the microcontroller, the clock system and the peripherals
 *
 * Initialization is done for the system, the user LEDs,
 * and the LCD display with the touchscreen.
 * @n Then the code enters an infinite while-loop in which it calls the menu.
 *
 * ----------------------------------------------------------------------------
 * @author  Fabian Erni, ernifab@students.zhaw.ch
 * @date	12.28.2021
 *****************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"

#include "menu.h"
#include "calculation.h"
#include "measuring.h"
#include "display.h"


/******************************************************************************
 * Defines
 *****************************************************************************/


/******************************************************************************
 * Variables
 *****************************************************************************/


/******************************************************************************
 * Functions
 *****************************************************************************/
static void MAIN_system_clock_config(void);
static void MAIN_gyro_disable(void);
static void MAIN_board_init(void);


/** ***************************************************************************
 * @brief Main function
 *
 * Initialization and infinite while loop.
 *****************************************************************************/
int main(void)
{
	MAIN_board_init();

	/* infinite while loop */
	while (1) {							// infinitely loop in main function
		BSP_LED_Toggle(LED3);			// visual feedback when running

		MENU_main();

		HAL_Delay(200);					// wait or sleep
	}
}


/** ***************************************************************************
 * @brief Board initialization
 *
 * Initialization of the various blocks.
 *****************************************************************************/
static void MAIN_board_init(void)
{
	/* initialize the system */
	HAL_Init();

	/* configure system clocks */
	MAIN_system_clock_config();

	/* initialize the LCD display */
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
	BSP_LCD_DisplayOn();
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* initialize the touch screen */
	BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());

	/* initialize the LED */
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);

	/* show info at startup */
	DISP_info_screen(MENU_HOME);

	/* disable gyro, use those analog inputs */
	MAIN_gyro_disable();

	/* configure GPIOs in analog mode */
	MEAS_GPIO_analog_init();
	/* configure the timer */
	MEAS_timer_init();
}


/** ***************************************************************************
 * @brief System clock configuration
 *
 * Configuration of the system clock.
 *****************************************************************************/
static void MAIN_system_clock_config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

	/* Configure the main internal regulator output voltage. */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Initialize High Speed External Oscillator and PLL circuits. */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 336;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	/* Initialize gates and clock dividers for CPU, AHB and APB busses. */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

	/* Initialize PLL and clock divider for the LCD. */
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
	PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
	PeriphClkInitStruct.PLLSAI.PLLSAIR = 4;
	PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_8;
	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

	/* Set clock prescaler for ADCs. */
	ADC->CCR |= ADC_CCR_ADCPRE_0;
}


/** ***************************************************************************
 * @brief Disable the GYRO on the microcontroller board
 *
 * Disable GYRO on PC1 and PF8 and set them as an analog input.
 * @note MISO of the GYRO is connected to PF8 and CS to PC1.
 * @n Some times the GYRO goes into an undefined mode at startup
 * and pulls the MISO low or high thus blocking the analog input on PF8.
 * @n The simplest solution is to pull the CS of the GYRO low for a short while
 * which is done with the code below.
 * @n PF8 is also reconfigured.
 * @n An other solution would be to remove the GYRO
 * from the microcontroller board by unsoldering it.
 *****************************************************************************/
static void MAIN_gyro_disable(void)
{
	__HAL_RCC_GPIOC_CLK_ENABLE();		// Enable Clock for GPIO port C
	GPIOC->MODER &= ~GPIO_MODER_MODER1; // Reset mode for PC1
	GPIOC->MODER |= GPIO_MODER_MODER1_0;	// Set PC1 as output
	GPIOC->BSRR |= GPIO_BSRR_BR1;		// Set GYRO (CS) to 0 for a short time
	HAL_Delay(10);						// Wait some time
	GPIOC->MODER |= GPIO_MODER_MODER1_Msk; 	// Analog mode PC1 = ADC123_IN11

	__HAL_RCC_GPIOF_CLK_ENABLE();		// Enable Clock for GPIO port F
	GPIOF->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED8;	// Reset speed of PF8
	GPIOF->AFR[1] &= ~GPIO_AFRH_AFSEL8;		// Reset alternate func. of PF8
	GPIOF->PUPDR &= ~GPIO_PUPDR_PUPD8;		// Reset pull up/down of PF8
	HAL_Delay(10);						// Wait some time
	GPIOF->MODER |= GPIO_MODER_MODER8_Msk; 	// Analog mode for PF8 = ADC3_IN4
}

