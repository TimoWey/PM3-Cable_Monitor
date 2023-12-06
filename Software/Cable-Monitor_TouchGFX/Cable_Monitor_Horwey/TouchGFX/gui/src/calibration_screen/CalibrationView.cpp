#include <gui/calibration_screen/CalibrationView.hpp>

CalibrationView::CalibrationView()
{

}

void CalibrationView::setupScreen()
{
    CalibrationViewBase::setupScreen();
}

void CalibrationView::tearDownScreen()
{
    CalibrationViewBase::tearDownScreen();
}

void CalibrationView::setTimeoutValue(int value)
{
	//display the timeout value on the GUI
	Unicode::snprintf(textArea3_1Buffer, TEXTAREA3_1_SIZE, "%d", value);
	textArea3_1.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
