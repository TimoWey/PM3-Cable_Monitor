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
