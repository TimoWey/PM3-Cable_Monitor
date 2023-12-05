#ifndef MEASUREMENT_ACCURATE_DISPLAY_2VIEW_HPP
#define MEASUREMENT_ACCURATE_DISPLAY_2VIEW_HPP

#include <gui_generated/measurement_accurate_display_2_screen/Measurement_Accurate_Display_2ViewBase.hpp>
#include <gui/measurement_accurate_display_2_screen/Measurement_Accurate_Display_2Presenter.hpp>

class Measurement_Accurate_Display_2View : public Measurement_Accurate_Display_2ViewBase
{
public:
    Measurement_Accurate_Display_2View();
    virtual ~Measurement_Accurate_Display_2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENT_ACCURATE_DISPLAY_2VIEW_HPP
