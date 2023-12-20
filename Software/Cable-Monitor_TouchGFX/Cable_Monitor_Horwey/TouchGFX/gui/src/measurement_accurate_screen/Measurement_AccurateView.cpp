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
	Unicode::snprintf(textArea_auto_offBuffer, TEXTAREA_AUTO_OFF_SIZE, "%d", value);
	textArea_auto_off.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
