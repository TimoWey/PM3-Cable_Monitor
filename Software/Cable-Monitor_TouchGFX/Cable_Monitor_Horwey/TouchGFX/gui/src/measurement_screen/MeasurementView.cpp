#include <gui/measurement_screen/MeasurementView.hpp>

MeasurementView::MeasurementView()
{

}

void MeasurementView::setupScreen()
{
    MeasurementViewBase::setupScreen();
}

void MeasurementView::tearDownScreen()
{
    MeasurementViewBase::tearDownScreen();
}

void MeasurementView::setTimeoutValue(int value)
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
