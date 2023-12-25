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

/**
 * @brief Sets the timeout value for the MeasurementView.
 *
 * This function sets the timeout value for the MeasurementView and updates the GUI accordingly.
 * If the timeout value is set to 0, it will navigate to the Shutting_OffScreenNoTransition.
 *
 * @param value The timeout value to be set.
 */
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
