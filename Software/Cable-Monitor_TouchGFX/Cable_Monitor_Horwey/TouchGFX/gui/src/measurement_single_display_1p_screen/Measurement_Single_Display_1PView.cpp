#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PView.hpp>

#ifndef SIMULATOR
#include "main.h"
#endif

Measurement_Single_Display_1PView::Measurement_Single_Display_1PView()
{

}

void Measurement_Single_Display_1PView::setupScreen()
{
    Measurement_Single_Display_1PViewBase::setupScreen();
}

void Measurement_Single_Display_1PView::tearDownScreen()
{
    Measurement_Single_Display_1PViewBase::tearDownScreen();
}

void Measurement_Single_Display_1PView::testGui()
{
#ifndef SIMULATOR
	int test = 	0;

	test = updateGUI_test();

	//update GUI values
	//set gauge angle
	SMD1_gauge.setValue(test);
	SMD1_gauge.invalidate();

	//set current value
	Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "%d", test);
	SMD1_Current.invalidate();

	//set frequency value
	Unicode::snprintf(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "%d", test);
	SMD1_Frequency.invalidate();

	//set distance value
	Unicode::snprintf(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "%d", test);
	SMD1_Distance.invalidate();
#endif
}

