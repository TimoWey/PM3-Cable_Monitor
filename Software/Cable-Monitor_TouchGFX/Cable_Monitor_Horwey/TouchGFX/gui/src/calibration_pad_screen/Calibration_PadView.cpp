#include <gui/calibration_pad_screen/Calibration_PadView.hpp>
#include <gui_generated/calibration_pad_screen/Calibration_PadViewBase.hpp>

#ifndef SIMULATOR

#include "main.h"


extern "C"
{
	#include "FLASH_SECTOR_F4.h"
	#include "calculation.h"
}

#endif

Calibration_PadView::Calibration_PadView()
{

}

void Calibration_PadView::setupScreen()
{
    Calibration_PadViewBase::setupScreen();
}

void Calibration_PadView::tearDownScreen()
{
    Calibration_PadViewBase::tearDownScreen();
}

void Calibration_PadView::setTimeoutValue(int value)
{

}

void Calibration_PadView::Load_FLASH_Values()
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
	Unicode::snprintf(textAreaCal_LH1_1A_1PBuffer, TEXTAREACAL_LH1_1A_1P_SIZE, "%d", Rx_Data[6]);
	Unicode::snprintf(textAreaCal_LH2_1A_1PBuffer, TEXTAREACAL_LH2_1A_1P_SIZE, "%d", Rx_Data[7]);

	// Hall Right 1P 1.2A and 5A
	Unicode::snprintf(textAreaCal_RH1_1A_1PBuffer, TEXTAREACAL_RH1_1A_1P_SIZE, "%d", Rx_Data[8]);
	Unicode::snprintf(textAreaCal_RH2_1A_1PBuffer, TEXTAREACAL_RH2_1A_1P_SIZE, "%d", Rx_Data[9]);

	// Hall Left  3P 1.2A and 5A
	Unicode::snprintf(textAreaCal_LH1_1A_3PBuffer, TEXTAREACAL_LH1_1A_3P_SIZE, "%d", Rx_Data[10]);
	Unicode::snprintf(textAreaCal_LH2_1A_3PBuffer, TEXTAREACAL_LH2_1A_3P_SIZE, "%d", Rx_Data[11]);

	// Hall Right 3P 1.2A and 5A
	Unicode::snprintf(textAreaCal_RH1_1A_3PBuffer, TEXTAREACAL_RH1_1A_3P_SIZE, "%d", Rx_Data[12]);
	Unicode::snprintf(textAreaCal_RH2_1A_3PBuffer, TEXTAREACAL_RH2_1A_3P_SIZE, "%d", Rx_Data[13]);

	// update swipe container
	swipeContainer1.invalidate();

#endif
}
