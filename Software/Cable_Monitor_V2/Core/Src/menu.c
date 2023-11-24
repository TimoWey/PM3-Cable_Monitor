/** ***************************************************************************
 * @file
 * @brief The menu of the graphical user interface(GUI)
 *
 * Initializes and displays the menu.
 * @note Provides the function MENU_check_transition() for polling user actions.
 * @n The variable MENU_transition is set to the touched menu item.
 * @n If no touch has occurred the variable MENU_transition is set to MENU_NONE
 * @n The different steps of the menu are executed in MENU_main().
 * @n The function MENU_get_transition() returns the new menu item.
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

#include "main.h"
#include "menu.h"
#include "calculation.h"
#include "display.h"


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
static MENU_entry_t MENU_entry[MENU_ENTRY_COUNT] = {
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
		///< fourth calibration, fifth cali current, sixth cali distance

/******************************************************************************
 * Functions
 *****************************************************************************/
static void MENU_check_transition(MENU_type_t type);
static uint8_t MENU_pad_cali(MENU_item_t command);
static uint8_t MENU_coil_cali(MENU_item_t command);
static MENU_item_t MENU_get_transition(void);


/** ***************************************************************************
 * @brief Get menu selection/transition
 *
 * @return Selected MENU_item or MENU_NONE if no MENU_item was selected
 *
 * MENU_transition is used as a flag.
 * @note When the value is read by calling MENU_get_transition()
 * this flag is cleared, respectively set to MENU_NONE.
 *****************************************************************************/
static MENU_item_t MENU_get_transition(void)
{
	MENU_item_t item = MENU_transition;
	MENU_transition = MENU_NONE;
	return item;
}


/** ***************************************************************************
 * @brief Check for selection/transition
 * @param[in] type	Actual menu type
 *
 * If the last transition has been consumed (MENU_NONE == MENU_transition)
 * @n and the touchscreen has been touched for a defined period
 * @n the variable MENU_transition is set to the touched item.
 * @note  Evalboard revision E (blue PCB) has an inverted y-axis
 * in the touch controller compared to the display.
 * @n Uncomment or comment the <b>\#define EVAL_REV_E</b> in main.h accordingly.
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
 * @brief Calibration menu for the distance
 * @param[in] command	Actual menu item
 * @return Actual calibration step for the distance
 *
 * Controls the calibration of the distance.
 *****************************************************************************/
static uint8_t MENU_pad_cali(MENU_item_t command)
{
	static CALC_cali_pad_step_t state_pad_cali = CALC_CALI_P_START;

	if (state_pad_cali >= CALC_CALI_P_END) {
		state_pad_cali = CALC_CALI_P_START;
	}
	if (state_pad_cali < CALC_CALI_P_FINISH) {
		switch (command) {
		case MENU_P_NE:
			state_pad_cali++;
			break;
		case MENU_P_AB:
			state_pad_cali = CALC_CALI_P_ABOARD;
			break;
		case MENU_P_BA:
			if (state_pad_cali != CALC_CALI_P_START) {
				state_pad_cali--;
			}
			break;
		default:						// Should never occur
			break;
		}
	} else {
		state_pad_cali++;
	}

	if (command != MENU_P_BA) {
		CALC_start_pad_calibration(state_pad_cali);
	}
	DISP_pad_calibration(state_pad_cali);
	if (state_pad_cali == CALC_CALI_P_FINISH) {
		state_pad_cali++;
	}
	return state_pad_cali;
}


/** ***************************************************************************
 * @brief Calibration menu for the current
 * @param[in] command	Actual menu item
 * @return Actual calibration step for the current
 *
 * Controls the calibration of the current.
 *****************************************************************************/
static uint8_t MENU_coil_cali(MENU_item_t command)
{
	static CALC_cali_coil_step_t state_coil_cali = CALC_CALI_C_START;
	static CALC_phase_item_t state_phase = CALC_ONE_PHASE;

	if (state_coil_cali >= CALC_CALI_C_END) {
		state_coil_cali = CALC_CALI_C_START;
	}
	if (state_coil_cali < CALC_CALI_C_FINISH) {
		switch (command) {
		case MENU_C_1P:
			state_coil_cali++;
			if (state_coil_cali == CALC_CALI_C_FIRST) {
				state_phase = CALC_ONE_PHASE;
			}
			break;
		case MENU_C_3P:
			state_coil_cali++;
			if (state_coil_cali == CALC_CALI_C_FIRST) {
				state_phase = CALC_THREE_PHASE;
			}
			break;
		case MENU_C_AB:
			state_coil_cali = CALC_CALI_C_ABOARD;
			break;
		default:						// Should never occur
			break;
		}
	} else {
		state_coil_cali++;
	}

	CALC_start_coil_calibration(state_phase, state_coil_cali);
	DISP_coil_calibration(state_coil_cali);
	if (state_coil_cali == CALC_CALI_C_FINISH) {
		state_coil_cali++;
	}
	return state_coil_cali;
}


/** ***************************************************************************
 * @brief Draw the menu on to the display.
 * @param[in] type	Actual menu type
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
 * @brief Master menu
 *
 * The master menu is responsible for the correct program guidance.
 * @n The menu of the graphical user interface (GUI) is generated by it.
 *****************************************************************************/
void MENU_main(void)
{
	static CALC_meas_data_t meas_data;
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
		CALC_start_single_measurement(&meas_data, CALC_ONE_PHASE);
		DISP_value_screen_sing(meas_data, CALC_ONE_PHASE);
		break;
	case MENU_S_3P:
		CALC_start_single_measurement(&meas_data, CALC_THREE_PHASE);
		DISP_value_screen_sing(meas_data, CALC_THREE_PHASE);
		break;

	case MENU_A_1P:
		CALC_start_accurate_measurement(&meas_data, CALC_ONE_PHASE);
		DISP_value_screen_accu(meas_data, CALC_ONE_PHASE);
		break;
	case MENU_A_3P:
		CALC_start_accurate_measurement(&meas_data, CALC_THREE_PHASE);
		DISP_value_screen_accu(meas_data, CALC_THREE_PHASE);
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
		if (MENU_coil_cali(MENU_C_1P) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
		break;
	case MENU_C_AB:
		if (MENU_coil_cali(MENU_C_AB) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
		break;
	case MENU_C_3P:
		if (MENU_coil_cali(MENU_C_3P) >= CALC_CALI_C_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
		break;

	case MENU_P_NE:
		if (MENU_pad_cali(MENU_P_NE) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
		break;
	case MENU_P_AB:
		if (MENU_pad_cali(MENU_P_AB) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
		break;
	case MENU_P_BA:
		if (MENU_pad_cali(MENU_P_BA) >= CALC_CALI_P_END) {
			menu = MENU_CALI;
			DISP_info_screen(menu);		// Show calibration menu
		}
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

