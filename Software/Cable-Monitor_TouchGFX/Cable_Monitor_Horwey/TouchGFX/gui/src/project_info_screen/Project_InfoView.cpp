#include <gui/project_info_screen/Project_InfoView.hpp>

Project_InfoView::Project_InfoView()
{

}

void Project_InfoView::setupScreen()
{
    Project_InfoViewBase::setupScreen();
}

void Project_InfoView::tearDownScreen()
{
    Project_InfoViewBase::tearDownScreen();
}

/**
 * @brief Sets the timeout value for the project information view.
 * 
 * This function updates the GUI to display the specified timeout value.
 * If the value is 0, it transitions to the shutting off screen.
 * 
 * @param value The timeout value to be set.
 */
void Project_InfoView::setTimeoutValue(int value)
{
	//display the timeout value on the GUI
	Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%d", value);
	textArea_auto_off.invalidate();

	if (value == 0) {
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
