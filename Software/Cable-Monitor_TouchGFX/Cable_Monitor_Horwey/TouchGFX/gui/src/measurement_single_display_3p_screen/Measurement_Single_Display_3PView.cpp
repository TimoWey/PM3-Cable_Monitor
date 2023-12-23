#include <gui/measurement_single_display_3p_screen/Measurement_Single_Display_3PView.hpp>

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

Measurement_Single_Display_3PView::Measurement_Single_Display_3PView()
{

}

void Measurement_Single_Display_3PView::setupScreen()
{
    Measurement_Single_Display_3PViewBase::setupScreen();
}

void Measurement_Single_Display_3PView::tearDownScreen()
{
    Measurement_Single_Display_3PViewBase::tearDownScreen();
}
void Measurement_Single_Display_3PView::single_meas_3PH(){
#ifndef SIMULATOR

	// set the screen timeout value
	sleep_timeout_value = SCREEN_TIMEOUT;

	// Disable TouchGFX Interrupts while the accurate measurement values are calculated
	DISABLE_TOUCHGFX_INTERRUPTS();

	// calculate single measurement values
	SINGLE_MEAS single_meas = single_measurement(THREE_PHASE);

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

	//update GUI values
	//set gauge angle
	SMD3_Gauge.setValue(single_meas.angle);
	SMD3_Gauge.invalidate();

	//set current value
	Unicode::snprintfFloat(SMD3_CurrentBuffer, SMD3_CURRENT_SIZE, "%.2f", single_meas.current);
	SMD3_Current.invalidate();

	//set frequency value
	Unicode::snprintfFloat(SMD3_FrequencyBuffer, SMD3_FREQUENCY_SIZE, "%.2f", single_meas.frequency);
	SMD3_Frequency.invalidate();

	//set distance value
	if(single_meas.distance >= 0 && single_meas.distance <= 200)
		Unicode::snprintfFloat(SMD3_DistanceBuffer, SMD3_DISTANCE_SIZE, "%.2f", single_meas.distance);
	else if(single_meas.distance < 0)
		Unicode::snprintf(SMD3_DistanceBuffer, SMD3_DISTANCE_SIZE, "0");
	else
		Unicode::snprintf(SMD3_DistanceBuffer, SMD3_DISTANCE_SIZE, "+200");
	SMD3_Distance.invalidate();

#endif
}
