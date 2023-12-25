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

/**
 * @brief Performs accurate 3-phase measurement and updates the display accordingly.
 * 
 * This function calculates the accurate measurement values for a 3-phase system and updates the display
 * with the calculated values. It also handles error conditions and displays appropriate error messages.
 * 
 * @note This function is only executed when not running in the simulator.
 */
void Measurement_Accurate_Display_3PView::accu_meas_3PH()
{
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
		Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "STDEV");
		Unicode::snprintf(AMD3_FrequencyBuffer, AMD3_FREQUENCY_SIZE, "TOO");
		Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "HIGH");
		AMD3_Gauge.setValue(0);
		AMD3_Gauge.invalidate();
        AMD3_Current.invalidate();
		AMD3_Frequency.invalidate();
		AMD3_Distance.invalidate();
    } else { 	// Output Values
		//set gauge angle
		AMD3_Gauge.setValue(accu_meas.angle);
		AMD3_Gauge.invalidate();

		// Check if there is an error with the current
		if(accu_meas.error_single == CALC_ERROR_OVERCURRENT){
			// Output error message
			Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "OVERCURRENT");
			AMD3_Current.invalidate();
		} else if(accu_meas.error_single == CALC_ERROR_TOO_FAR_AWAY){
			// Output error message
			Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "TOO FAR");
			AMD3_Current.invalidate();
		} else{
			// set current value
			// Check if current is within range of 0 - 10 A
			if(accu_meas.current >= 0 && accu_meas.current <= 10){
				Unicode::snprintfFloat(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "%.2f A", accu_meas.current);
				AMD3_Current.invalidate();
			} else {
				Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "TOO FAR");
				AMD3_Current.invalidate();
			}
		}

		// Check if there is an error with the frequency
		if(accu_meas.error_single == CALC_ERROR_FREQUENCY){
			// Output error message
			Unicode::snprintf(AMD3_FrequencyBuffer, AMD3_FREQUENCY_SIZE, "NO SIGNAL");
			AMD3_Frequency.invalidate();
		} else{
			//set frequency value
			Unicode::snprintfFloat(AMD3_FrequencyBuffer, AMD3_FREQUENCY_SIZE, "%.2f Hz", accu_meas.frequency);
			AMD3_Frequency.invalidate();
		}

		// Check if there is an error with the distance
		if(accu_meas.error_single == CALC_ERROR_DISCONNECT){
			// Output error message
			Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "DISCONNECTED");
			Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "DISCONNECTED");
			Unicode::snprintf(AMD3_FrequencyBuffer, AMD3_FREQUENCY_SIZE, "NO SIGNAL");
			AMD3_Frequency.invalidate();
			AMD3_Distance.invalidate();
			AMD3_Current.invalidate();
		} else{
			//set distance value
			// Check if distance is within range of 0 to 200 mm
			if(accu_meas.distance >= 0 && accu_meas.distance <= 200)
				Unicode::snprintfFloat(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "%.2f mm", accu_meas.distance);
			else if(accu_meas.distance < 0)
				Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "0 mm");
			else{
				Unicode::snprintf(AMD3_DistanceBuffer, AMD3_DISTANCE_SIZE, "+200 mm");
				Unicode::snprintf(AMD3_CurrentBuffer, AMD3_CURRENT_SIZE, "TOO FAR");
			}
			AMD3_Distance.invalidate();
			AMD3_Current.invalidate();
		}
	}

	// Enable TouchGFX Interrupts after the accurate measurement values are calculated
	ENABLE_TOUCHGFX_INTERRUPTS();

#endif
}
