#ifndef MEASUREMENT_SINGLE_DISPLAY_1PVIEW_HPP
#define MEASUREMENT_SINGLE_DISPLAY_1PVIEW_HPP

#include <gui_generated/measurement_single_display_1p_screen/Measurement_Single_Display_1PViewBase.hpp>
#include <gui/measurement_single_display_1p_screen/Measurement_Single_Display_1PPresenter.hpp>

class Measurement_Single_Display_1PView : public Measurement_Single_Display_1PViewBase
{
public:
    Measurement_Single_Display_1PView();
    virtual ~Measurement_Single_Display_1PView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENT_SINGLE_DISPLAY_1PVIEW_HPP
