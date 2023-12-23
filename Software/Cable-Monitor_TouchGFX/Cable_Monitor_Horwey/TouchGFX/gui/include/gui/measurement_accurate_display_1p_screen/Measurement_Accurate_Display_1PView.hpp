#ifndef MEASUREMENT_ACCURATE_DISPLAY_1PVIEW_HPP
#define MEASUREMENT_ACCURATE_DISPLAY_1PVIEW_HPP

#include <gui_generated/measurement_accurate_display_1p_screen/Measurement_Accurate_Display_1PViewBase.hpp>
#include <gui/measurement_accurate_display_1p_screen/Measurement_Accurate_Display_1PPresenter.hpp>

class Measurement_Accurate_Display_1PView : public Measurement_Accurate_Display_1PViewBase
{
public:
    Measurement_Accurate_Display_1PView();
    virtual ~Measurement_Accurate_Display_1PView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void setTimeoutValue(int value);
protected:
};

#endif // MEASUREMENT_ACCURATE_DISPLAY_1PVIEW_HPP
