#include <gui/calibration_pad_screen/Calibration_PadView.hpp>

#ifndef SIMULATOR
#include "main.h"
#include "stm32f4xx_hal_gpio.h"

extern "C" {
#include "calculation.h"
#include "measuring.h"
#define ARM_MATH_CM4
#include "arm_math.h"
}

#endif

Calibration_PadView::Calibration_PadView() {}

void Calibration_PadView::setupScreen() {
    Calibration_PadViewBase::setupScreen();
}

void Calibration_PadView::tearDownScreen() {
    Calibration_PadViewBase::tearDownScreen();
}

void Calibration_PadView::setTimeoutValue(int value) {}

void Calibration_PadView::function_cali_pad() {
#ifndef SIMULATOR
	
	uint32_t* Samples = MEAS_start_measure();
	FFT fft = calculate_freq_and_signalstrength(1, Samples);
    Unicode::snprintfFloat(CALIBRATION_PADR_SBuffer, CALIBRATION_PADR_S_SIZE,
                           "%.2f", fft.signal_strength);
    CALIBRATION_PADR_S.invalidate();
    Unicode::snprintfFloat(CALIBRATION_PADR_FBuffer, CALIBRATION_PADR_F_SIZE,
                           "%.2f", fft.main_freq);
    CALIBRATION_PADR_F.invalidate();

    fft = calculate_freq_and_signalstrength(2, Samples);

    Unicode::snprintfFloat(CALIBRATION_PADL_SBuffer, CALIBRATION_PADL_S_SIZE,
                           "%.2f", fft.signal_strength);
    CALIBRATION_PADL_S.invalidate();
    Unicode::snprintfFloat(CALIBRATION_PADL_FBuffer, CALIBRATION_PADL_F_SIZE,
                           "%.2f", fft.main_freq);
    CALIBRATION_PADL_F.invalidate();

#endif
}
