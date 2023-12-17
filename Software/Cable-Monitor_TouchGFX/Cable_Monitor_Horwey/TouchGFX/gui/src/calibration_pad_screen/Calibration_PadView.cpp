#include <gui/calibration_pad_screen/Calibration_PadView.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "FLASH_SECTOR_F4.h"

//extern "C"
//{
//	#include "FLASH_SECTOR_F4.h"
//}

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

	//Load the 6 Calibration Values from the Flash
	//uint32_t Rx_Data[6];

	//Flash_Read_Data(SECTOR_23_ADDR, Rx_Data, 6);

#endif
}
