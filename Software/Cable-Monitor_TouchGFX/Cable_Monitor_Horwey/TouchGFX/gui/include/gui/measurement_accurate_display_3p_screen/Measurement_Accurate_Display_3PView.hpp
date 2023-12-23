#ifndef MEASUREMENT_ACCURATE_DISPLAY_3PVIEW_HPP
#define MEASUREMENT_ACCURATE_DISPLAY_3PVIEW_HPP

#include <gui_generated/measurement_accurate_display_3p_screen/Measurement_Accurate_Display_3PViewBase.hpp>
#include <gui/measurement_accurate_display_3p_screen/Measurement_Accurate_Display_3PPresenter.hpp>

class Measurement_Accurate_Display_3PView : public Measurement_Accurate_Display_3PViewBase
{
public:
    Measurement_Accurate_Display_3PView();
    virtual ~Measurement_Accurate_Display_3PView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void accu_meas_3PH();

protected:
};

#endif // MEASUREMENT_ACCURATE_DISPLAY_3PVIEW_HPP
