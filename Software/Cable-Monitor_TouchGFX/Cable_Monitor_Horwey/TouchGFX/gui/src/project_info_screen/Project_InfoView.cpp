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
	Unicode::snprintf(textArea3_1Buffer, TEXTAREA3_1_SIZE, "%d", value);
	textArea3_1.invalidate();

	if (value == 0) {
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
