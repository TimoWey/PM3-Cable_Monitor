/** ***************************************************************************
 * @file
 * @brief USER pushbutton
 *
 * Initializes the GPIO for the pushbutton.
 * @n Enables the interrupt on the pushbutton.
 * @n Implements the interrupt handler for the pushbutton.
 *
 * @author  Hanspeter Hochreutener, hhrt@zhaw.ch
 * @date	16.04.2020
 *****************************************************************************/

/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"

#include "GPIO.h"

/******************************************************************************
 * Defines
 *****************************************************************************/

/******************************************************************************
 * Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/

/** ***************************************************************************
 * @brief Configure the GPIO for the USER pushbutton
 *
 * The USER pushbutton is connected to PA0.
 *****************************************************************************/
void GPIO_Init(void) {
	// Configure PE5 as Output
	/*__HAL_RCC_GPIOG_CLK_ENABLE();
	 GPIOE-> MODER |= 0x400;
	 GPIOE-> OSPEEDR |= 0x400;
	 HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);*/

	// Initialize the GPIO pins
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_GPIOE_CLK_ENABLE(); // Enable the GPIO E clock

	// Configure PE3 in input mode
	GPIO_InitStruct.Pin = PIN_PE3;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// Configure PE5 in output push-pull mode -> Soft latching power Circuit drive (Keeps board On)
	GPIO_InitStruct.Pin = PIN_PE5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// Configure PE15 in output push-pull mode -> Used for LED_1 (Right LED)
	GPIO_InitStruct.Pin = LED_RIGHT;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// Configure PE13 in output push-pull mode -> Used for LED_2 (Left LED)
	GPIO_InitStruct.Pin = LED_LEFT;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	// Automatically Keeps Board alive (Soft latching circuit) by setting PIN5->High
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);
	while (HAL_GPIO_ReadPin(GPIOE, PIN_PE3) == GPIO_PIN_SET) {
		HAL_Delay(100);
	}
	HAL_Delay(3000);
}
