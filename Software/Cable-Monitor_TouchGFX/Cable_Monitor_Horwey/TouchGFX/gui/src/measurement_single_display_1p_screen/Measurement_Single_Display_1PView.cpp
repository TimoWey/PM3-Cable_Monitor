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

	uint32_t* Samples = MEAS_start_measure();

	//callback to fft
	FFT fft = calculate_freq_and_signalstrength(1, Samples);

	DISTANCE_ANGLE distance_angle = calculate_distance_and_angle(Samples);

	//update GUI values
	//set gauge angle
	SMD1_gauge.setValue(distance_angle.angle);
	SMD1_gauge.invalidate();

	//set current value
	Unicode::snprintfFloat(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "%.2f", distance_angle.angle);
	SMD1_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "%.2f", fft.main_freq);
	SMD1_Frequency.invalidate();

	//set distance value
	Unicode::snprintfFloat(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "%.2f", distance_angle.distance);
	SMD1_Distance.invalidate();


	//temp
	Unicode::snprintfFloat(Pad_LBuffer, PAD_L_SIZE, "%.2f", distance_angle.distance_l);
	Pad_L.invalidate();
	Unicode::snprintfFloat(Pad_RBuffer, PAD_R_SIZE, "%.2f", distance_angle.distance_r);
	Pad_R.invalidate();

#endif
}

