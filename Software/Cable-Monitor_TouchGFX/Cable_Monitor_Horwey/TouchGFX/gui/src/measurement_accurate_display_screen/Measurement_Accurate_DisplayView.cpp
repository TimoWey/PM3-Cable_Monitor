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

	// Check if standard deviation is too high
	if (accu_meas.error_accu == CALC_ERROR_DEVIATION_TOO_HIGH) {
        // Output error message
        Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "STDEV");
		Unicode::snprintf(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "STDEV");
		Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "STDEV");
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
			//set current value
			Unicode::snprintfFloat(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "%.2f", accu_meas.current);
			AMD1_Current.invalidate();
		}

		// Check if there is an error with the frequency
		if(accu_meas.error_single == CALC_ERROR_FREQUENCY){
			// Output error message
			Unicode::snprintf(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "NO SIGNAL");
			AMD1_Frequency.invalidate();
		} else{
			//set frequency value
			Unicode::snprintfFloat(AMD1_FrequencyBuffer, AMD1_FREQUENCY_SIZE, "%.2f", accu_meas.frequency);
			AMD1_Frequency.invalidate();
		}

		// Check if there is an error with the distance
		if(accu_meas.error_single == CALC_ERROR_DISCONNECT){
			// Output error message
			Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "DISCONNECTED");
			Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "DISCONNECTED");
			AMD1_Distance.invalidate();
			AMD1_Current.invalidate();
		} else{
			//set distance value
			if(accu_meas.distance >= 0 && accu_meas.distance <= 200)
				Unicode::snprintfFloat(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "%.2f", accu_meas.distance);
			else if(accu_meas.distance < 0)
				Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "0");
			else{
				Unicode::snprintf(AMD1_DistanceBuffer, AMD1_DISTANCE_SIZE, "+200");
				Unicode::snprintf(AMD1_CurrentBuffer, AMD1_CURRENT_SIZE, "DISCONNECTED");
			}
			AMD1_Distance.invalidate();
			AMD1_Current.invalidate();
		}
	}

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

#endif
}
