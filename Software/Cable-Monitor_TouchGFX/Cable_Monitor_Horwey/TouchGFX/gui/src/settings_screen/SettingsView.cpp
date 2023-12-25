#include <gui/settings_screen/SettingsView.hpp>

#ifndef SIMULATOR

#include "main.h"

extern "C"
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

void SettingsView::toggle_BUZZER()
{
#ifndef SIMULATOR
	// callback to function in calculation.c to toggle the buzzer
	toggle_Buzzer_settings(true);
#endif
}

void SettingsView::toggle_LED()
{
#ifndef SIMULATOR
	// callback to function in calculation.c to toggle the buzzer
	toggle_Buzzer_settings(false);
#endif
}
