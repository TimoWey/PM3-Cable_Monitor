/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

// insert small sample mainpage here for doxygen
/**
   \mainpage Main Page
    \section intro_sec Introduction
    This is the introduction.
    \section install_sec Installation
    \subsection main.c handels...
    \subsection calculation.c handels...
    \subsection measureing.c handels...
    \subsection FLASH_SECTOR_F4.c handels...
    \subsection TouchGFX Folder includes...
    \subsection How to use
    \section Testing
    \section Bugs
    \section conclusion Conclusion
    This is the conclusion.
*/


/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void setCalibrationFlashValues(uint32_t StartSectorAddress, uint32_t value, uint32_t index, uint16_t numberofwords);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VSYNC_FREQ_Pin GPIO_PIN_2
#define VSYNC_FREQ_GPIO_Port GPIOE
#define DEVICE_ON_OFF_TRIGGER_Pin GPIO_PIN_3
#define DEVICE_ON_OFF_TRIGGER_GPIO_Port GPIOE
#define DEVICE_ON_OFF_TRIGGER_EXTI_IRQn EXTI3_IRQn
#define FRAME_RATE_Pin GPIO_PIN_4
#define FRAME_RATE_GPIO_Port GPIOE
#define POWER_ON_DEVICE_Pin GPIO_PIN_5
#define POWER_ON_DEVICE_GPIO_Port GPIOE
#define LED_PWM_Pin GPIO_PIN_0
#define LED_PWM_GPIO_Port GPIOA
#define BUZZER_PWM_Pin GPIO_PIN_7
#define BUZZER_PWM_GPIO_Port GPIOA
#define DEBUG_GPIO_Pin GPIO_PIN_4
#define DEBUG_GPIO_GPIO_Port GPIOC
#define DEVICE_ON_Pin GPIO_PIN_13
#define DEVICE_ON_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */
/**
 * @brief Address of sector 23 in flash memory.
 */
#define SECTOR_23_ADDR 0x081E0000


/**
 * @brief The timeout value (in seconds) for the screen to automatically turn off.
 */
#define SCREEN_TIMEOUT 180

extern int sleep_timeout_value;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
