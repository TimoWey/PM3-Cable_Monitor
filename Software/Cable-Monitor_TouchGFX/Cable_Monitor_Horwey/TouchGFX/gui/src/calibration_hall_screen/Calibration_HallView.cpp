#include <gui/calibration_hall_screen/Calibration_HallView.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

//extern "C"
//{
//	#include "measuring.h"
//	#include "calculation.h"
//	#define ARM_MATH_CM4
//	#include "arm_math.h"
//}

#endif

Calibration_HallView::Calibration_HallView()
{

}

void Calibration_HallView::setupScreen()
{
    Calibration_HallViewBase::setupScreen();
}

void Calibration_HallView::tearDownScreen()
{
    Calibration_HallViewBase::tearDownScreen();
}

void Calibration_HallView::setTimeoutValue(int value)
{

}

void Calibration_HallView::function_cali_hall_sensor()
{
#ifndef SIMULATOR

	//uint32_t* Samples = MEAS_start_measure();
	//FFT fft = calculate_freq_and_signalstrength(3, Samples);

	Unicode::snprintfFloat(CALIBRATION_HSR_SBuffer, CALIBRATION_HSR_S_SIZE, "%.2f", 0.0);
	CALIBRATION_HSR_S.invalidate();
	Unicode::snprintfFloat(CALIBRATION_HSR_FBuffer, CALIBRATION_HSR_F_SIZE, "%.2f", 0.0);
	CALIBRATION_HSR_F.invalidate();

	//fft = calculate_freq_and_signalstrength(4, Samples);

	Unicode::snprintfFloat(CALIBRATION_HSL_SBuffer, CALIBRATION_HSL_S_SIZE, "%.2f", 0.0);
	CALIBRATION_HSL_S.invalidate();
	Unicode::snprintfFloat(CALIBRATION_HSL_FBuffer, CALIBRATION_HSL_F_SIZE, "%.2f", 0.0);
	CALIBRATION_HSL_F.invalidate();

#endif
}
