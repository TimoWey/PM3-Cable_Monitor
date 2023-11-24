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


/******************************************************************************
 * Defines
 *****************************************************************************/


/******************************************************************************
 * Types
 *****************************************************************************/
/** Enumeration of possible main menu types */
typedef enum {
	MENU_HOME = 0, 	///< Home menu
	MENU_M_SI, 		///< Single measurement menu
	MENU_M_AC, 		///< Accurate measurement menu
	MENU_CALI, 		///< Calibration menu
	MENU_C_CO, 		///< Current calibration menu
	MENU_C_PA 		///< Distance calibration menu
} MENU_type_t;


/** Struct with fields of a menu entry */
typedef struct {
	char line1[16]; 		///< First line of menu text
	char line2[16]; 		///< Second line of menu text
	uint32_t text_color; 	///< Text color
	uint32_t back_color; 	///< Background color
} MENU_entry_t;


/******************************************************************************
 * Functions
 *****************************************************************************/
void MENU_main(void);
void MENU_draw(MENU_type_t type);


#endif	/* MENU_H_ */

