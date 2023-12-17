/** ***************************************************************************
 * @file
 * @brief See pushbutton.c
 *
 * Prefix: PB
 *
 *****************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_


/******************************************************************************
 * Includes
 *****************************************************************************/
#include <stdbool.h>


/******************************************************************************
 * Defines
 *****************************************************************************/
#define PIN_PE3 GPIO_PIN_3
#define PIN_PE5 GPIO_PIN_5

/******************************************************************************
 * Functions
 *****************************************************************************/
void GPIO_Init(void);


#endif