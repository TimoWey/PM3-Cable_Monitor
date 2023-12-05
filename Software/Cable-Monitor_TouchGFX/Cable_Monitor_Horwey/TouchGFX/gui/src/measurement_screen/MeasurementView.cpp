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
	Unicode::snprintf(textArea3_1Buffer, TEXTAREA3_1_SIZE, "%d", value);
	textArea3_1.invalidate();

	if(value == 0)
	{
		//application().gotoMeasurement_SingleScreenSlideTransitionWest();
		application().gotoShutting_OffScreenNoTransition();
	}
}
