#include <gui/measurement_single_screen/Measurement_SingleView.hpp>

Measurement_SingleView::Measurement_SingleView()
{

}

void Measurement_SingleView::setupScreen()
{
    Measurement_SingleViewBase::setupScreen();
}

void Measurement_SingleView::tearDownScreen()
{
    Measurement_SingleViewBase::tearDownScreen();
}

void Measurement_SingleView::setTimeoutValue(int value)
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
