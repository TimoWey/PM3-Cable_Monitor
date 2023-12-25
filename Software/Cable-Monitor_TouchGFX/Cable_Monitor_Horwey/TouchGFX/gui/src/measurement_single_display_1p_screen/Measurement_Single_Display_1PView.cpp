#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PView.hpp>

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

void Measurement_Single_Display_1PView::single_measure()
{
#ifndef SIMULATOR

	// set the screen timeout value
	sleep_timeout_value = SCREEN_TIMEOUT;

	// Disable TouchGFX Interrupts while the accurate measurement values are calculated
	DISABLE_TOUCHGFX_INTERRUPTS();

	// calculate single measurement values
	SINGLE_MEAS single_meas = single_measurement(SINGLE_PHASE);

	//update GUI values
	//set gauge angle
	SMD1_Gauge.setValue(single_meas.angle);
	SMD1_Gauge.invalidate();

	// Check if there is an error with the current
	if(single_meas.error == CALC_ERROR_OVERCURRENT){
		// Output error message
		Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "OVERCURRENT");
		SMD1_Current.invalidate();
	} else if(single_meas.error == CALC_ERROR_TOO_FAR_AWAY){
		// Output error message
		Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "TOO FAR");
		SMD1_Current.invalidate();
	} else{
		//set current value
		Unicode::snprintfFloat(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "%.2f A", single_meas.current);
		SMD1_Current.invalidate();
	}
	
	// Check if there is an error with the frequency
	if(single_meas.error == CALC_ERROR_FREQUENCY){
		// Output error message
		Unicode::snprintf(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "NO SIGNAL");
		SMD1_Frequency.invalidate();
	} else{
		//set frequency value
		Unicode::snprintfFloat(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "%.2f Hz", single_meas.frequency);
		SMD1_Frequency.invalidate();
	}

	// Check if there is an error with the distance
	if(single_meas.error == CALC_ERROR_DISCONNECT){
		// Output error message
		Unicode::snprintf(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "DISCONNECTED");
		Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "DISCONNECTED");
		Unicode::snprintf(SMD1_FrequencyBuffer, SMD1_FREQUENCY_SIZE, "NO SIGNAL");
		SMD1_Frequency.invalidate();
		SMD1_Distance.invalidate();
		SMD1_Current.invalidate();
	} else{
		//set distance value
		if(single_meas.distance >= 0 && single_meas.distance <= 200)
			Unicode::snprintfFloat(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "%.2f mm", single_meas.distance);
		else if(single_meas.distance < 0)
			Unicode::snprintf(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "0 mm");
		else{
			Unicode::snprintf(SMD1_DistanceBuffer, SMD1_DISTANCE_SIZE, "+200 mm");
			Unicode::snprintf(SMD1_CurrentBuffer, SMD1_CURRENT_SIZE, "DISCONNECTED");
		}
		SMD1_Distance.invalidate();
		SMD1_Current.invalidate();
	}

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

#endif
}

