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
#define MENU_FONT				&Font12	///< Possible font sizes: 8 12 16 20 24
#define MENU_HEIGHT				40		///< Height of menu bar
#define MENU_MARGIN				2		///< Margin around a menu entry
/** Position of menu bar: 0 = top, (BSP_LCD_GetYSize()-MENU_HEIGHT) = bottom */
#define MENU_Y					(BSP_LCD_GetYSize()-MENU_HEIGHT)


/******************************************************************************
 * Variables
 *****************************************************************************/
static MENU_item_t MENU_transition = MENU_NONE;	///< Transition to this menu

static MENU_entry_t MENU_entry[MENU_ENTRY_COUNT] = {
		{"Measurement",	"-",			LCD_COLOR_BLACK,	LCD_COLOR_LIGHTBLUE},
		{"Calibration",	"-",			LCD_COLOR_BLACK,	LCD_COLOR_LIGHTGREEN},
		{"Info",	    "-",			LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},

		//MEASUREMENTS
		{"Single",		"Measurement",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTBLUE},
		{"Accurate",	"Measurement",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTBLUE},
		{"Return",		"to Home",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},

		//SINGLE
		{"Single",		"Measurement",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTBLUE},
		{"Return",		"to Home",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},

		//ACCURATE
		{"Accurate",	"Measurement",	LCD_COLOR_BLACK,	LCD_COLOR_LIGHTBLUE},
		{"Return",		"to Home",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},

		//CALIBRATION
		{"Calibrate",	"-",			LCD_COLOR_BLACK,	LCD_COLOR_LIGHTGREEN},
		{"Return",		"to Home",		LCD_COLOR_BLACK,	LCD_COLOR_LIGHTRED},
};		///< All the menu entries


/******************************************************************************
 * Functions
 *****************************************************************************/


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
	static MENU_item_t menu = MENU_HOME;

	/* Comment next line if touchscreen interrupt is enabled */
	MENU_check_transition(menu);

	switch (MENU_get_transition())
	{	// Handle user menu choice
		case MENU_HOME:
            // Handle home menu selection
			MENU_hint();
			MENU_draw(0, 3);
            break;
        case MENU_MEASUREMENTS:
			MENU_Measurements();
        	MENU_draw(4, 7);
            // Handle measurements menu selection
            break;
        case MENU_SINGLE:
            // Handle single menu selection
            break;
        case MENU_ACCURATE:
            // Handle accurate menu selection
            break;
        case MENU_CALIBRATION:
			MENU_Calibrations();
			MENU_draw(10, 11);
            // Handle calibration menu selection
            break;
        case MENU_INFO:
			MENU_Info();
            // Handle info menu selection
            break;
		case MENU_RETURN:
			menu = MENU_HOME;
			break;
        case MENU_NONE:
            // Handle none menu selection
            break;
        default:
            // Handle invalid menu selection
            break;
		/*case MENU_ZERO:
			ADC3_IN4_single_init();
			ADC3_IN4_single_read();
			break;
		case MENU_ONE:
			ADC3_IN4_timer_init();
			ADC3_IN4_timer_start();
			break;
		case MENU_TWO:
			ADC3_IN4_DMA_init();
			ADC3_IN4_DMA_start();
			break;
		case MENU_THREE:
			ADC1_IN13_ADC2_IN5_dual_init();
			ADC1_IN13_ADC2_IN5_dual_start();
			break;
		case MENU_FOUR:
			ADC2_IN13_IN5_scan_init();
			ADC2_IN13_IN5_scan_start();
			break;
		case MENU_FIVE:
			ADC3_IN13_IN4_scan_init();
			ADC3_IN13_IN4_scan_start();
			break;*/
	}
}



/** ***************************************************************************
 * @brief Draw the menu onto the display.
 *
 * Each menu entry has two lines.
 * Text and background colors are applied.
 * @n These attributes are defined in the variable MENU_draw[].
 *****************************************************************************/
void MENU_draw(uint8_t start_item, uint8_t end_item)
{
	uint8_t count = end_item - start_item;
	
	BSP_LCD_SetFont(MENU_FONT);
	uint32_t x, y, m, w, h;
	y = MENU_Y;
	m = MENU_MARGIN;
	w = BSP_LCD_GetXSize()/count;
	h = MENU_HEIGHT;
	
	
	for (uint8_t i = start_item; i < end_item; i++) 
	{
		x = i*w;
		BSP_LCD_SetTextColor(MENU_entry[i].back_color);
		BSP_LCD_FillRect(x+m, y+m, w-2*m, h-2*m);
		BSP_LCD_SetBackColor(MENU_entry[i].back_color);
		BSP_LCD_SetTextColor(MENU_entry[i].text_color);
		BSP_LCD_DisplayStringAt(x+3*m, y+3*m,
				(uint8_t *)MENU_entry[i].line1, LEFT_MODE);
		BSP_LCD_DisplayStringAt(x+3*m, y+h/2,
				(uint8_t *)MENU_entry[i].line2, LEFT_MODE);
	}
}


/** ***************************************************************************
 * @brief Shows a hint at startup.
 *
 *****************************************************************************/
void MENU_hint(void)
{
	BSP_LCD_Clear(LCD_COLOR_WHITE);
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
void MENU_check_transition(MENU_item_t menu)
{

	static MENU_item_t item_old = MENU_NONE;
	static MENU_item_t item_new = MENU_NONE;
	static TS_StateTypeDef  TS_State;	// State of the touch controller
	uint32_t menu_offset = 0;
	BSP_TS_GetState(&TS_State);			// Get the state


// Evalboard revision E (blue) has an inverted y-axis in the touch controller
#ifdef EVAL_REV_E
	TS_State.Y = BSP_LCD_GetYSize() - TS_State.Y;	// Invert the y-axis
#endif
	// Invert x- and y-axis if LCD ist flipped
#ifdef FLIPPED_LCD
	TS_State.X = BSP_LCD_GetXSize() - TS_State.X;	// Invert the x-axis
	TS_State.Y = BSP_LCD_GetYSize() - TS_State.Y;	// Invert the y-axis
#endif


/*
	#if (defined(EVAL_REV_E) && !defined(FLIPPED_LCD)) || (!defined(EVAL_REV_E) && defined(FLIPPED_LCD))
	TS_State.Y = BSP_LCD_GetYSize() - TS_State.Y;	// Invert the y-axis
#endif
#ifdef EVAL_REV_E
#endif
*/

	if (TS_State.TouchDetected) {		// If a touch was detected
		/* Do only if last transition not pending anymore */
		if (MENU_NONE == MENU_transition) {
			item_old = item_new;		// Store old item
			/* If touched within the menu bar? */
			if ((MENU_Y < TS_State.Y) && (MENU_Y+MENU_HEIGHT > TS_State.Y)) {
				//Calculate which menu is next
				if(menu < MENU_NUM_NUM_ENTRIES) {
					menu_offset = menu*MENU_NUM_MENU_ELEMENTS; //calculate the menu
				}
				
				item_new = TS_State.X	// Calculate new item
						/ (BSP_LCD_GetXSize()/MENU_NUM_MENU_ELEMENTS);
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

