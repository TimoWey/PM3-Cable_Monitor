#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PView.hpp>

extern "C"
{
#include "main.h"
}


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

void Measurement_Single_Display_1PView::testGui()
{
	int test = 	0;

	test = updateGUI_test();

	test = test + 1;


	//touchgfx::Gauge* myGaugeWidget = &Gauge_with_Values.gauge1();
	//myGaugeWidget->setValue(newValue);
	//gauge_with_Values1.invalidate();

	//gauge_with_Values1->gauge1.setValue(10);
	//Gauge_with_ValuesBase->setValue(test);

	//Gauge_with_ValuesBase.gauge1.setValue(test);
	//Gauge_with_ValuesBase.gauge1.invalidate();
}

