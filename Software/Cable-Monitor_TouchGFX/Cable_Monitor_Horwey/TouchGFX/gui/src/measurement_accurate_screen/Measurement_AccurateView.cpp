#include <gui/measurement_accurate_screen/Measurement_AccurateView.hpp>

Measurement_AccurateView::Measurement_AccurateView()
{

}

void Measurement_AccurateView::setupScreen()
{
    Measurement_AccurateViewBase::setupScreen();
}

void Measurement_AccurateView::tearDownScreen()
{
    Measurement_AccurateViewBase::tearDownScreen();
}

void Measurement_AccurateView::setTimeoutValue(int value)
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
