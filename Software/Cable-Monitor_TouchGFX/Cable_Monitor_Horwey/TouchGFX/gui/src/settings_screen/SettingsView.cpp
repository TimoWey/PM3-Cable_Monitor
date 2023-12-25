#include <gui/settings_screen/SettingsView.hpp>

#ifndef SIMULATOR

#include "main.h"

extern "C"
/**
 * @brief This section includes the necessary header files for the SettingsView.cpp file.
 *        It includes "main.h" and "calculation.h".
 *        It also declares the external variable "State_BUZZER".
 */
{
#include "main.h"
#include "calculation.h"
extern bool State_BUZZER;
}

#endif

SettingsView::SettingsView()
{

}

void SettingsView::setupScreen()
{
    SettingsViewBase::setupScreen();
}

void SettingsView::tearDownScreen()
{
    SettingsViewBase::tearDownScreen();
}

/**
 * @brief Sets the timeout value for the settings view.
 *
 * This function updates the GUI to display the specified timeout value.
 * If the value is 0, it also navigates to the shutting off screen without any transition.
 *
 * @param value The timeout value to be set.
 */
void SettingsView::setTimeoutValue(int value)
{
	//display the timeout value on the GUI
	Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%d", value);
	textArea_auto_off.invalidate();

	if(value == 0)
	{
		application().gotoShutting_OffScreenNoTransition();
	}
}

/**
 * @brief Toggles the buzzer.
 * 
 * This function is used to toggle the buzzer on or off. It calls a callback function
 * in calculation.c to perform the actual toggling of the buzzer. This function is only
 * executed if the code is not running in a simulator.
 */
void SettingsView::toggle_BUZZER()
{
#ifndef SIMULATOR
	// callback to function in calculation.c to toggle the buzzer
	toggle_Buzzer_settings(true);
#endif
}

/**
 * @brief Toggles the LED.
 * 
 * This function is used to toggle the LED on the device. It checks if the code is running on a simulator or not.
 * If it is not running on a simulator, it calls the toggle_Buzzer_settings function in calculation.c to toggle the buzzer.
 */
void SettingsView::toggle_LED()
{
#ifndef SIMULATOR
	// callback to function in calculation.c to toggle the buzzer
	toggle_Buzzer_settings(false);
#endif
}
