#include <gui/calibration_pad_screen/Calibration_PadView.hpp>
#include <gui_generated/calibration_pad_screen/Calibration_PadViewBase.hpp>

#ifndef SIMULATOR

#include "main.h"


extern "C"
{
	#include "FLASH_SECTOR_F4.h"

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
	uint32_t Rx_Data[6];

	//Load the 6 Calibration Values from the Flash
	Flash_Read_Data(0x081E0000, Rx_Data, 6);

	// Write current Data stored in the Flash to the GUI
	//Left Pad
	Unicode::snprintf(textAreaCal_LP1Buffer, TEXTAREACAL_LP1_SIZE, "%d", Rx_Data[0]);
	Unicode::snprintf(textAreaCal_LP2Buffer, TEXTAREACAL_LP2_SIZE, "%d", Rx_Data[1]);
	Unicode::snprintf(textAreaCal_LP3Buffer, TEXTAREACAL_LP3_SIZE, "%d", Rx_Data[2]);
	//Right Pad
	Unicode::snprintf(textAreaCal_RP1Buffer, TEXTAREACAL_RP1_SIZE, "%d", Rx_Data[3]);
	Unicode::snprintf(textAreaCal_RP2Buffer, TEXTAREACAL_RP2_SIZE, "%d", Rx_Data[4]);
	Unicode::snprintf(textAreaCal_RP3Buffer, TEXTAREACAL_RP3_SIZE, "%d", Rx_Data[5]);
	swipeContainer1.invalidate();


#endif
}
