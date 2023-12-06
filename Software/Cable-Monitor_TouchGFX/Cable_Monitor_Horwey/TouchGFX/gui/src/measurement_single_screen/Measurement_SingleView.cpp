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
	Unicode::snprintf(textArea3_1Buffer, TEXTAREA3_1_SIZE, "%d", value);
	textArea3_1.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
