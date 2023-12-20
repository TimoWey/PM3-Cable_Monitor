#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PView.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

extern "C"
{
	#include "measuring.h"
	#include "calculation.h"

}

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

	// Start measurement
	uint32_t* Samples = MEAS_start_measure();

	// calculate single measurement values
	SINGLE_MEAS single_meas = single_measurement(Samples);

	//update GUI values
	//set gauge angle
	SMD1_Gauge.setValue(single_meas.angle);
	SMD1_Gauge.invalidate();

	//set current value
	Unicode::snprintfFloat(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "%.2f", 420.69);
	SMD1_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "%.2f", single_meas.frequency);
	SMD1_Frequency.invalidate();

	//set distance value
	Unicode::snprintfFloat(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "%.2f", single_meas.distance);
	SMD1_Distance.invalidate();

#endif
}

