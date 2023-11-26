/** ***************************************************************************
 * @file
 * @brief The menu
 *
 * Initializes and displays the menu.
 * @n Provides the function MENU_check_transition() for polling user actions.
 * The variable MENU_transition is set to the touched menu item.
 * If no touch has occurred the variable MENU_transition is set to MENU_NONE
 * @n If the interrupt handler is enabled by calling BSP_TS_ITConfig();
 * the variable MENU_transition is set to the touched menu entry as above.
 * @n Either call once BSP_TS_ITConfig() to enable the interrupt
 * or MENU_check_transition() in the main while loop for polling.
 * @n The function MENU_get_transition() returns the new menu item.
 *
 * @author  Hanspeter Hochreutener, hhrt@zhaw.ch
 * @date	30.04.2020
 *****************************************************************************/


/******************************************************************************
 * Includes
 *****************************************************************************/
#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ts.h"

#include "main.h"

#include "menu.h"


/******************************************************************************
 * Defines
 *****************************************************************************/
#define MENU_NUM_OF_DIFF_MENU	6 ///< Number of different menu pages
#define MENU_NUM_OF_MENU_ELEM	3 ///< Number of menu elements on the page
#define MENU_ENTRY_COUNT		MENU_NUM_OF_DIFF_MENU*MENU_NUM_OF_MENU_ELEM
								  ///< Number of menu entries
#define MENU_FONT				&Font12 ///< Possible font sizes: 8 12 16 20 24
#define MENU_HEIGHT				40 ///< Height of menu bar
#define MENU_MARGIN				2 ///< Margin around a menu entry
/** Position of menu bar: 0 = top, (BSP_LCD_GetYSize()-MENU_HEIGHT) = bottom */
#define MENU_Y					(BSP_LCD_GetYSize()-MENU_HEIGHT)


/******************************************************************************
 * Types
 *****************************************************************************/
/** Enumeration of possible menu items */
typedef enum {
	MENU_SING = 0,	///< Single measurement button
	MENU_ACCU,		///< Accurate measurement button
	MENU_CALB,		///< Calibration button

	MENU_S_1P,		///< Single measurement one phase button
	MENU_S_HO,		///< Single measurement home button
	MENU_S_3P,		///< Single measurement three phase button

	MENU_A_1P,		///< Accurate measurement one phase button
	MENU_A_HO,		///< Accurate measurement home button
	MENU_A_3P,		///< Accurate measurement three phase button

	MENU_C_CI,		///< Calibration current button
	MENU_C_HO,		///< Calibration home button
	MENU_C_PD,		///< Calibration distance button

	MENU_C_1P,		///< Calibration current one phase button
	MENU_C_AB,		///< Calibration current aboard button
	MENU_C_3P,		///< Calibration current three phase button

	MENU_P_NE,		///< Calibration distance next button
	MENU_P_AB,		///< Calibration distance aboard button
	MENU_P_BA,		///< Calibration distance back button

	MENU_NONE		///< Do nothing
} MENU_item_t;

/******************************************************************************
 * Variables
 *****************************************************************************/
static MENU_item_t MENU_transition = MENU_NONE;	///< Transition to this menu

static MENU_entry_t MENU_entry[MENU_ENTRY_COUNT] =
{
	{"single",	"measurem.",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTCYAN},
	{"accurate","measurem.",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTGREEN},
	{"calibra.","screen",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTMAGENTA},

	{"1.phase",	"measurem.",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTCYAN},
	{"home",	"screen",		LCD_COLOR_WHITE,	LCD_COLOR_GRAY},
	{"3.phase",	"measurem.",	LCD_COLOR_WHITE,	LCD_COLOR_DARKCYAN},

	{"1.phase",	"measurem.",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTGREEN},
	{"home",	"screen",		LCD_COLOR_WHITE,	LCD_COLOR_GRAY},
	{"3.phase",	"measurem.",	LCD_COLOR_WHITE,	LCD_COLOR_DARKGREEN},

	{"calibra.","current",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},
	{"home",	"screen",		LCD_COLOR_WHITE,	LCD_COLOR_GRAY},
	{"calibra.","distance",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTYELLOW},

	{"1.phase",	"current",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},
	{"abort",	"current",		LCD_COLOR_WHITE,	LCD_COLOR_GRAY},
	{"3.phase", "current",		LCD_COLOR_WHITE,	LCD_COLOR_BROWN},

	{"next",	"distance",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTYELLOW},
	{"abort",	"distance",		LCD_COLOR_WHITE,	LCD_COLOR_GRAY},
	{"back",	"distance",		LCD_COLOR_WHITE,	LCD_COLOR_ORANGE},
};		///< first block home menu, second meas single, third meas accurate,
		///< fourth calibration, fifth cali current, sixth cali distance		///< All the menu entries


/******************************************************************************
 * Functions
 *****************************************************************************/
static void MENU_check_transition(MENU_type_t type);
static MENU_item_t MENU_get_transition(void);

/** ***************************************************************************
 * @brief Handles the main menu state machine.
 *
 * Each menu entry has two lines.
 * Text and background colors are applied.
 * @n These attributes are defined in the variable MENU_draw[].
 *****************************************************************************/
void MENU_main(void)
{
	//static CALC_meas_data_t meas_data;
	static MENU_type_t menu = MENU_HOME;

	MENU_check_transition(menu);

	switch (MENU_get_transition()) {	// Handle user menu choice
	case MENU_NONE:						// No transition => do nothing
		break;

	case MENU_SING:
		menu = MENU_M_SI;
		DISP_info_screen(menu);			// Show single meas. menu
		break;
	case MENU_ACCU:
		menu = MENU_M_AC;
		DISP_info_screen(menu);			// Show accurate meas. menu
		break;
	case MENU_CALB:
		menu = MENU_CALI;
		DISP_info_screen(menu);			// Show calibration menu
		break;

	case MENU_S_1P:
		//CALC_start_single_measurement(&meas_data, CALC_ONE_PHASE);
		//DISP_value_screen_sing(meas_data, CALC_ONE_PHASE);
		break;
	case MENU_S_3P:
		//CALC_start_single_measurement(&meas_data, CALC_THREE_PHASE);
		//DISP_value_screen_sing(meas_data, CALC_THREE_PHASE);
		break;

	case MENU_A_1P:
		//CALC_start_accurate_measurement(&meas_data, CALC_ONE_PHASE);
		//DISP_value_screen_accu(meas_data, CALC_ONE_PHASE);
		break;
	case MENU_A_3P:
		//CALC_start_accurate_measurement(&meas_data, CALC_THREE_PHASE);
		//DISP_value_screen_accu(meas_data, CALC_THREE_PHASE);
		break;

	case MENU_C_PD:
		menu = MENU_C_PA;
		DISP_info_screen(menu);			// Show distance calibration menu
		break;
	case MENU_C_CI:
		menu = MENU_C_CO;
		DISP_info_screen(menu);			// Show current calibration menu
		break;

	case MENU_C_1P:
		/*if (MENU_coil_cali(MENU_C_1P) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;
	case MENU_C_AB:
		/*if (MENU_coil_cali(MENU_C_AB) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;
	case MENU_C_3P:
		/*if (MENU_coil_cali(MENU_C_3P) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;

	case MENU_P_NE:
		/*if (MENU_pad_cali(MENU_P_NE) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;
	case MENU_P_AB:
		/*if (MENU_pad_cali(MENU_P_AB) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;
	case MENU_P_BA:
		/*if (MENU_pad_cali(MENU_P_BA) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}*/
		break;

	case MENU_C_HO:
	case MENU_A_HO:
	case MENU_S_HO:
		menu = MENU_HOME;
		DISP_info_screen(menu);			// Show home menu
		break;
	default:							// Should never occur
		break;
	}
}

/** ***************************************************************************
 * @brief Displays the info screen
 * @param[in] type	Actual menu type
 *
 * Displays the title and information on each screen.
 *****************************************************************************/
void DISP_info_screen(MENU_type_t type)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);		//Clear display
	MENU_draw(type);					//Draw the home menu

	switch (type) {
	case MENU_HOME:
		/* Show info home */
		MENU_hint();
		break;
	case MENU_M_SI:
		/* Show info single meas. */
		//DISP_info_measurement((uint8_t *)"Single Meas.");
		break;
	case MENU_M_AC:
		/* Show info accurate meas. */
		//DISP_info_measurement((uint8_t *)"Accurate Meas.");
		break;
	case MENU_CALI:
		/* Show info calibration */
		//DISP_info_calibration();
		break;
	case MENU_C_CO:
		/* Show coil info calibration */
		//DISP_info_cali_coil();
		break;
	case MENU_C_PA:
		/* Show pad info calibration */
		//DISP_info_cali_pad();
		break;
	default:
		/* Should never occur */
		break;
	}
}



/** ***************************************************************************
 * @brief Draw the menu onto the display.
 *
 * Each menu entry has two lines.
 * Text and background colors are applied.
 * @n These attributes are defined in the variable MENU_draw[].
 *****************************************************************************/
void MENU_draw(MENU_type_t type)
{
	BSP_LCD_SetFont(MENU_FONT);
	uint32_t x, y, m, w, h, offset;
	y = MENU_Y;
	m = MENU_MARGIN;
	w = BSP_LCD_GetXSize()/MENU_NUM_OF_MENU_ELEM;
	h = MENU_HEIGHT;
	offset = 0;
	if (type < MENU_NUM_OF_DIFF_MENU) {
		offset = type*MENU_NUM_OF_MENU_ELEM;	//calculate the menu
	}
	for (uint32_t i = 0; i < MENU_NUM_OF_MENU_ELEM; i++) {
		x = i*w;
		BSP_LCD_SetTextColor(MENU_entry[i+offset].back_color);
		BSP_LCD_FillRect(x+m, y+m, w-2*m, h-2*m);
		BSP_LCD_SetBackColor(MENU_entry[i+offset].back_color);
		BSP_LCD_SetTextColor(MENU_entry[i+offset].text_color);
		BSP_LCD_DisplayStringAt(x+3*m, y+3*m,
				(uint8_t *)MENU_entry[i+offset].line1, LEFT_MODE);
		BSP_LCD_DisplayStringAt(x+3*m, y+h/2,
				(uint8_t *)MENU_entry[i+offset].line2, LEFT_MODE);
	}
}

/** ***************************************************************************
 * @brief Shows a hint at startup.
 *
 *****************************************************************************/
void MENU_hint(void)
{
	//BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0,10, (uint8_t *)"Cable-Monitor", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0,30, (uint8_t *) "by Alejandro & Timo", CENTER_MODE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(5, 60, (uint8_t *)"1. Touch a menu item", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 80, (uint8_t *)"to start a cable", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 100, (uint8_t *)"measurement:", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 120, (uint8_t *)"Single or Accurate.", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 150, (uint8_t *)"Version: 01.00", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 170, (uint8_t *)"Data: 17.12.2023", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 190, (uint8_t *)"Authors: Horvat, Wey", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 210, (uint8_t *)"Modul: ET.PM3 ZHAW", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 230, (uint8_t *)"Lecturers: Matic &", LEFT_MODE);
	BSP_LCD_DisplayStringAt(5, 250, (uint8_t *)"Ehrensperger", LEFT_MODE);
}

/** ***************************************************************************
 * @brief Shows a hint at startup.
 *
 *****************************************************************************/
void MENU_Measurements(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0,10, (uint8_t *)"Cable-Monitor", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0,30, (uint8_t *) "by Alejandro & Timo", CENTER_MODE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(5, 60, (uint8_t *)"Menu: Measurements", LEFT_MODE);
}

/** ***************************************************************************
 * @brief Shows a hint at startup.
 *
 *****************************************************************************/
void MENU_Calibrations(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0,10, (uint8_t *)"Cable-Monitor", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0,30, (uint8_t *) "by Alejandro & Timo", CENTER_MODE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(5, 60, (uint8_t *)"Menu: Calibrations", LEFT_MODE);
}

/** ***************************************************************************
 * @brief Shows a hint at startup.
 *
 *****************************************************************************/
void MENU_Info(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0,10, (uint8_t *)"Cable-Monitor", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0,30, (uint8_t *) "by Alejandro & Timo", CENTER_MODE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(5, 60, (uint8_t *)"Menu: Info", LEFT_MODE);
}


/** ***************************************************************************
 * @brief Set a menu entry.
 * @param [in] item number of menu bar
 * @param [in] entry attributes for that item
 *
 * @note Call MENU_draw() to update the display.
 *****************************************************************************/
void MENU_set_entry(const MENU_item_t item, const MENU_entry_t entry)
{
	if ((0 <= item) && (MENU_ENTRY_COUNT > item)) {
		MENU_entry[item] = entry;
	}
}


/** ***************************************************************************
 * @brief Get a menu entry.
 * @param [in] item number of menu bar
 * @return Menu_entry[item] or Menu_entry[0] if item not in range
 *****************************************************************************/
MENU_entry_t MENU_get_entry(const MENU_item_t item)
{
	MENU_entry_t entry = MENU_entry[0];
	if ((0 <= item) && (MENU_ENTRY_COUNT > item)) {
		entry = MENU_entry[item];
	}
	return entry;
}


/** ***************************************************************************
 * @brief Get menu selection/transition
 *
 * @return the selected MENU_item or MENU_NONE if no MENU_item was selected
 *
 * MENU_transition is used as a flag.
 * When the value is read by calling MENU_get_transition()
 * this flag is cleared, respectively set to MENU_NONE.
 *****************************************************************************/
MENU_item_t MENU_get_transition(void)
{
	MENU_item_t item = MENU_transition;
	MENU_transition = MENU_NONE;
	return item;
}

/** ***************************************************************************
 * @brief Check for selection/transition
 *
 * If the last transition has been consumed (MENU_NONE == MENU_transition)
 * and the touchscreen has been touched for a defined period
 * the variable MENU_transition is set to the touched item.
 * @note  Evalboard revision E (blue PCB) has an inverted y-axis
 * in the touch controller compared to the display.
 * Uncomment or comment the <b>\#define EVAL_REV_E</b> in main.h accordingly.
 *****************************************************************************/
static void MENU_check_transition(MENU_type_t type)
{
	static MENU_item_t item_old = MENU_NONE;
	static MENU_item_t item_new = MENU_NONE;
	static TS_StateTypeDef  TS_State;	// State of the touch controller
	uint32_t offset = 0;
	BSP_TS_GetState(&TS_State);			// Get the state
#ifdef EVAL_REV_E
/* Evalboard revision E (blue) has an inverted y-axis in the touch controller */
	TS_State.Y = BSP_LCD_GetYSize() - TS_State.Y;	// Invert the y-axis
#endif
	if (TS_State.TouchDetected) {		// If a touch was detected
		/* Do only if last transition not pending anymore */
		if (MENU_NONE == MENU_transition) {
			item_old = item_new;		// Store old item
			/* If touched within the menu bar? */
			if ((MENU_Y < TS_State.Y) && (MENU_Y+MENU_HEIGHT > TS_State.Y)) {
				if(type < MENU_NUM_OF_DIFF_MENU) {
					offset = type*MENU_NUM_OF_MENU_ELEM; //calculate the menu
				}
				item_new = (TS_State.X	// Calculate new item
						/ (BSP_LCD_GetXSize()/MENU_NUM_OF_MENU_ELEM)) + offset;
				if ((0 > item_new) || (MENU_ENTRY_COUNT <= item_new)) {
					item_new = MENU_NONE;	// Out of bounds
				}
				if (item_new == item_old) {	// 2 times the same menu item
					item_new = MENU_NONE;
					MENU_transition = item_old;
				}
			}
		}
	}
}



/** ***************************************************************************
 * @brief Interrupt handler for the touchscreen
 *
 * @note BSP_TS_ITConfig(); must be called in the main function
 * to enable touchscreen interrupt.
 * @note There are timing issues when interrupt is enabled.
 * It seems that polling is the better choice with this evaluation board.
 * @n Call MENU_check_transition() from the while loop in main for polling.
 *
 * The touchscreen interrupt is connected to PA15.
 * @n The interrupt handler for external line 15 to 10 is called.
 *****************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & EXTI_PR_PR15) {		// Check if interrupt on touchscreen
		EXTI->PR |= EXTI_PR_PR15;		// Clear pending interrupt on line 15
		if (BSP_TS_ITGetStatus()) {		// Get interrupt status
			BSP_TS_ITClear();				// Clear touchscreen controller int.
			MENU_check_transition(MENU_NONE);
		}
		EXTI->PR |= EXTI_PR_PR15;		// Clear pending interrupt on line 15
	}
}

