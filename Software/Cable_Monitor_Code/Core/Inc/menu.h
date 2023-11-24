/** ***************************************************************************
 * @file
 * @brief See menu.c
 *
 * Prefix MENU
 *
 *****************************************************************************/

#ifndef MENU_H_
#define MENU_H_


/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stdint.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define MENU_NUM_NUM_ENTRIES	5		///< Number of diffrent menu layers
#define MENU_NUM_MENU_ELEMENTS	3		///< Number of menu elements per layer
///< Total number of menu entries
#define MENU_ENTRY_COUNT 		(MENU_NUM_NUM_ENTRIES * MENU_NUM_MENU_ELEMENTS)



/******************************************************************************
 * Types
 *****************************************************************************/
/** Enumeration of possible menu items */
typedef enum {
	MENU_HOME = 0,
	MENU_MEASUREMENTS,
	MENU_SINGLE,
	MENU_ACCURATE,
	MENU_RETURN,
	MENU_CALIBRATION,
	MENU_INFO,
	MENU_NONE
} MENU_item_t;

/** Struct with fields of a menu entry */
typedef struct {
	char line1[16];						///< First line of menu text
	char line2[16];						///< Second line of menu text
	uint32_t text_color;				///< Text color
	uint32_t back_color;				///< Background color
} MENU_entry_t;


/******************************************************************************
 * Functions
 *****************************************************************************/
void MENU_main(void);
void MENU_draw(uint8_t start_item, uint8_t end_item);
void MENU_hint(void);
void MENU_Measurements(void);
void MENU_Calibrations(void);
void MENU_Info(void);
void MENU_set_entry(const MENU_item_t item, const MENU_entry_t entry);
MENU_entry_t MENU_get_entry(const MENU_item_t item);
void MENU_check_transition(MENU_item_t menu);
MENU_item_t MENU_get_transition(void);


#endif

