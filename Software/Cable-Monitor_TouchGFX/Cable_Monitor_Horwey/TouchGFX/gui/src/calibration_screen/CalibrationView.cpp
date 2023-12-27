#include <gui/calibration_screen/CalibrationView.hpp>

#ifndef SIMULATOR

#include "main.h"


extern "C"
/**
 * @brief This section includes the necessary header files for the calibration screen.
 * 
 * The "FLASH_SECTOR_F4.h" header file provides access to functions related to flash sector operations.
 * The "calculation.h" header file provides access to functions related to calculations.
 */
{
	#include "FLASH_SECTOR_F4.h"
	#include "calculation.h"
}

#endif

CalibrationView::CalibrationView()
{

}

void CalibrationView::setupScreen()
{
    CalibrationViewBase::setupScreen();
}

void CalibrationView::tearDownScreen()
{
    CalibrationViewBase::tearDownScreen();
}

void CalibrationView::setTimeoutValue(int value)
{

}

/**
 * @brief Loads the calibration values from the Flash memory and updates the GUI.
 * 
 * This function reads the calibration values stored in the Flash memory and writes them to the corresponding GUI elements.
 * The calibration values include left pad, right pad, hall left 1P 1.2A and 5A, hall right 1P 1.2A and 5A,
 * hall left 3P 1.2A and 5A, and hall right 3P 1.2A and 5A.
 * 
 * @note This function is only executed when not running in the simulator.
 */
void CalibrationView::Load_FLASH_Values()
{
#ifndef SIMULATOR

	SwipeContainer swipeContainer = swipeContainer1;
	uint32_t Rx_Data[14];

	//Load the 6 Calibration Values from the Flash
	Flash_Read_Data(0x081E0000, Rx_Data, 14);

	// Write current Data stored in the Flash to the GUI
	//Left Pad
	Unicode::snprintf(textAreaCal_LP1Buffer, TEXTAREACAL_LP1_SIZE, "%d", Rx_Data[0]);
	Unicode::snprintf(textAreaCal_LP2Buffer, TEXTAREACAL_LP2_SIZE, "%d", Rx_Data[1]);
	Unicode::snprintf(textAreaCal_LP3Buffer, TEXTAREACAL_LP3_SIZE, "%d", Rx_Data[2]);
	//Right Pad
	Unicode::snprintf(textAreaCal_RP1Buffer, TEXTAREACAL_RP1_SIZE, "%d", Rx_Data[3]);
	Unicode::snprintf(textAreaCal_RP2Buffer, TEXTAREACAL_RP2_SIZE, "%d", Rx_Data[4]);
	Unicode::snprintf(textAreaCal_RP3Buffer, TEXTAREACAL_RP3_SIZE, "%d", Rx_Data[5]);
	// Hall Left  1P 1.2A and 5A
	Unicode::snprintf(textAreaCal_LH_1A_1PBuffer, TEXTAREACAL_LH_1A_1P_SIZE, "%d", Rx_Data[6]);
	Unicode::snprintf(textAreaCal_LH_5A_1PBuffer, TEXTAREACAL_LH_5A_1P_SIZE, "%d", Rx_Data[7]);
	// Hall Right 1P 1.2A and 5A
	Unicode::snprintf(textAreaCal_RH_1A_1PBuffer, TEXTAREACAL_RH_1A_1P_SIZE, "%d", Rx_Data[8]);
	Unicode::snprintf(textAreaCal_RH_5A_1PBuffer, TEXTAREACAL_RH_5A_1P_SIZE, "%d", Rx_Data[9]);
	// Hall Left  3P 1.2A and 5A
	Unicode::snprintf(textAreaCal_LH_1A_3PBuffer, TEXTAREACAL_LH_1A_3P_SIZE, "%d", Rx_Data[10]);
	Unicode::snprintf(textAreaCal_LH_5A_3PBuffer, TEXTAREACAL_LH_5A_3P_SIZE, "%d", Rx_Data[11]);
	// Hall Right 3P 1.2A and 5A
	Unicode::snprintf(textAreaCal_RH_1A_3PBuffer, TEXTAREACAL_RH_1A_3P_SIZE, "%d", Rx_Data[12]);
	Unicode::snprintf(textAreaCal_RH_5A_3PBuffer, TEXTAREACAL_RH_5A_3P_SIZE, "%d", Rx_Data[13]);

	// update swipe container
	swipeContainer1.invalidate();

#endif
}
