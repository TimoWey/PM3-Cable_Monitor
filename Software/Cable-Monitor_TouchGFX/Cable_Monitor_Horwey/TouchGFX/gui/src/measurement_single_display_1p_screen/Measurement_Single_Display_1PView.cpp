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
	// Disable Touchgfx tasks to avoid interference
	touchgfx::HAL::getInstance()->disableInterrupts();

	int test = 	0;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);

	test = updateGUI_test();

	uint32_t* Samples = MEAS_start_measure();

	//callback to fft
	FFT fft = calculate_freq_and_signalstrength(1, Samples, 50);

	//update GUI values
	//set gauge angle
	SMD1_gauge.setValue(test);
	SMD1_gauge.invalidate();

	//set current value
	Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "%d", test);
	SMD1_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "%.2f", fft.main_freq);
	SMD1_Frequency.invalidate();

	//set distance value
	Unicode::snprintfFloat(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "%.2f", fft.signal_strength);
	SMD1_Distance.invalidate();

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);

	// Enable Touchgfx tasks
	touchgfx::HAL::getInstance()->enableInterrupts();

#endif
}

