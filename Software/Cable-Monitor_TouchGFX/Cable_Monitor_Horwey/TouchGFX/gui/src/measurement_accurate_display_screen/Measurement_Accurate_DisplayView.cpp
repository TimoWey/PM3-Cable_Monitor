#include <gui/measurement_accurate_display_screen/Measurement_Accurate_DisplayView.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

extern "C"
{
	#include "main.h"
	#include "measuring.h"
	#include "calculation.h"
}

#endif

Measurement_Accurate_DisplayView::Measurement_Accurate_DisplayView()
{

}

void Measurement_Accurate_DisplayView::setupScreen()
{
    Measurement_Accurate_DisplayViewBase::setupScreen();
}

void Measurement_Accurate_DisplayView::tearDownScreen()
{
    Measurement_Accurate_DisplayViewBase::tearDownScreen();
}

void Measurement_Accurate_DisplayView::accu_meas(){
#ifndef SIMULATOR

	// set the screen timeout value
	sleep_timeout_value = SCREEN_TIMEOUT;

	// Disable TouchGFX Interrupts while the accurate measurement values are calculated
	DISABLE_TOUCHGFX_INTERRUPTS();

	// calculate single measurement values
	ACCU_MEAS accu_meas = accurate_measurement(SINGLE_PHASE);

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

	//update GUI values
	//set gauge angle
	AMD1_Gauge.setValue(accu_meas.angle);
	AMD1_Gauge.invalidate();

	//set current value
	Unicode::snprintfFloat(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "%.2f", accu_meas.current);
	AMD1_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "%.2f", accu_meas.frequency);
	AMD1_Frequency.invalidate();

	//set distance value
	if(accu_meas.distance >= 0 && accu_meas.distance <= 200)
		Unicode::snprintfFloat(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "%.2f", accu_meas.distance);
	else if(accu_meas.distance < 0)
		Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "0");
	else
		Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "+200");
	AMD1_Distance.invalidate();

#endif
}
