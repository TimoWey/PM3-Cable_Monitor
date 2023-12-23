#include <gui/measurement_accurate_display_3p_screen/Measurement_Accurate_Display_3PView.hpp>

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
Measurement_Accurate_Display_3PView::Measurement_Accurate_Display_3PView()
{

}

void Measurement_Accurate_Display_3PView::setupScreen()
{
    Measurement_Accurate_Display_3PViewBase::setupScreen();
}

void Measurement_Accurate_Display_3PView::tearDownScreen()
{
    Measurement_Accurate_Display_3PViewBase::tearDownScreen();
}

void Measurement_Accurate_Display_3PView::accu_meas_3PH(){
#ifndef SIMULATOR

	// set the screen timeout value
	sleep_timeout_value = SCREEN_TIMEOUT;

	// Disable TouchGFX Interrupts while the accurate measurement values are calculated
	DISABLE_TOUCHGFX_INTERRUPTS();

	// calculate single measurement values
	ACCU_MEAS accu_meas = accurate_measurement(THREE_PHASE);

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

	//update GUI values
	//set gauge angle
	AMD3_Gauge.setValue(accu_meas.angle);
	AMD3_Gauge.invalidate();

	//set current value
	Unicode::snprintfFloat(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "%.2f", 420.69);
	AMD3_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(AMD3_FrequencyBuffer, AMD3_FREQUENCY_SIZE, "%.2f", accu_meas.frequency);
	AMD3_Frequency.invalidate();

	//set distance value
	if(accu_meas.distance >= 0 && accu_meas.distance <= 200)
		Unicode::snprintfFloat(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "%.2f", accu_meas.distance);
	else if(accu_meas.distance < 0)
		Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "0");
	else
		Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "+200");
	AMD3_Distance.invalidate();

#endif
}
