#include <gui/main_menu_screen/Main_MenuView.hpp>

Main_MenuView::Main_MenuView()
{

}

void Main_MenuView::setupScreen()
{
    Main_MenuViewBase::setupScreen();
}

void Main_MenuView::tearDownScreen()
{
    Main_MenuViewBase::tearDownScreen();
}

/**
 * @brief Sets the timeout value for the main menu screen.
 * 
 * This function updates the timeout value displayed on the GUI and invalidates the text area.
 * If the value is 0, it navigates to the shutting off screen without any transition.
 * 
 * @param value The timeout value to be set.
 */
void Main_MenuView::setTimeoutValue(int value)
{
	//display the timeout value on the GUI
	Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%d", value);
	textArea_auto_off.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
