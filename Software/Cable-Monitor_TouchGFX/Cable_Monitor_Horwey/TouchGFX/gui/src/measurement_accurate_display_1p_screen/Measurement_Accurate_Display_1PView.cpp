#include <gui/measurement_accurate_display_1p_screen/Measurement_Accurate_Display_1PView.hpp>

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

Measurement_Accurate_Display_1PView::Measurement_Accurate_Display_1PView()
{

}

void Measurement_Accurate_Display_1PView::setupScreen()
{
    Measurement_Accurate_Display_1PViewBase::setupScreen();
}

void Measurement_Accurate_Display_1PView::tearDownScreen()
{
    Measurement_Accurate_Display_1PViewBase::tearDownScreen();
}

void Measurement_Accurate_Display_1PView::setTimeoutValue(int value)
{

}

void Measurement_Accurate_Display_1PView::accu_meas(){
#ifndef SIMULATOR

	// set the screen timeout value
	sleep_timeout_value = SCREEN_TIMEOUT;

	// Disable TouchGFX Interrupts while the accurate measurement values are calculated
	DISABLE_TOUCHGFX_INTERRUPTS();

	// calculate single measurement values
	ACCU_MEAS accu_meas = accurate_measurement(SINGLE_PHASE);

	// Check if standard deviation is too high
	if (accu_meas.error_accu == CALC_ERROR_DEVIATION_TOO_HIGH) {
        // Output error message
		Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "STDEV");
		Unicode::snprintf(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "TOO");
		Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "HIGH");
		AMD1_Gauge.setValue(0);
		AMD1_Gauge.invalidate();
        AMD1_Current.invalidate();
		AMD1_Frequency.invalidate();
		AMD1_Distance.invalidate();
    } else { 	// Output Values
		//set gauge angle
		AMD1_Gauge.setValue(accu_meas.angle);
		AMD1_Gauge.invalidate();

		// Check if there is an error with the current
		if(accu_meas.error_single == CALC_ERROR_OVERCURRENT){
			// Output error message
			Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "OVERCURRENT");
			AMD1_Current.invalidate();
		} else if(accu_meas.error_single == CALC_ERROR_TOO_FAR_AWAY){
			// Output error message
			Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "TOO FAR");
			AMD1_Current.invalidate();
		} else{
			// set current value
			// Check if current is within range of 0 - 10 A
			if(accu_meas.current >= 0 && accu_meas.current <= 10){
				Unicode::snprintfFloat(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "%.2f A", accu_meas.current);
				AMD1_Current.invalidate();
			} else {
				Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "TOO FAR");
				AMD1_Current.invalidate();
			}
		}

		// Check if there is an error with the frequency
		if(accu_meas.error_single == CALC_ERROR_FREQUENCY){
			// Output error message
			Unicode::snprintf(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "NO SIGNAL");
			AMD1_Frequency.invalidate();
		} else{
			//set frequency value
			Unicode::snprintfFloat(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "%.2f Hz", accu_meas.frequency);
			AMD1_Frequency.invalidate();
		}

		// Check if there is an error with the distance
		if(accu_meas.error_single == CALC_ERROR_DISCONNECT){
			// Output error message
			Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "DISCONNECTED");
			Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "DISCONNECTED");
			Unicode::snprintf(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "NO SIGNAL");
			AMD1_Frequency.invalidate();
			AMD1_Distance.invalidate();
			AMD1_Current.invalidate();
		} else{
			//set distance value
			// Check if distance is within range of 0 to 200 mm
			if(accu_meas.distance >= 0 && accu_meas.distance <= 200)
				Unicode::snprintfFloat(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "%.2f mm", accu_meas.distance);
			else if(accu_meas.distance < 0)
				Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "0 mm");
			else{
				Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "+200 mm");
				Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "TOO FAR");
			}
			AMD1_Distance.invalidate();
			AMD1_Current.invalidate();
		}
	}

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

#endif
}

