#ifndef MEASUREMENT_SINGLE_DISPLAY_3PVIEW_HPP
#define MEASUREMENT_SINGLE_DISPLAY_3PVIEW_HPP

#include <gui_generated/measurement_single_display_3p_screen/Measurement_Single_Display_3PViewBase.hpp>
#include <gui/measurement_single_display_3p_screen/Measurement_Single_Display_3PPresenter.hpp>

class Measurement_Single_Display_3PView : public Measurement_Single_Display_3PViewBase
{
public:
    Measurement_Single_Display_3PView();
    virtual ~Measurement_Single_Display_3PView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENT_SINGLE_DISPLAY_3PVIEW_HPP
