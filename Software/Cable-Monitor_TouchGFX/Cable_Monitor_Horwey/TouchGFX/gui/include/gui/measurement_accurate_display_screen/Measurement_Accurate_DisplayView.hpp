#ifndef MEASUREMENT_ACCURATE_DISPLAYVIEW_HPP
#define MEASUREMENT_ACCURATE_DISPLAYVIEW_HPP

#include <gui_generated/measurement_accurate_display_screen/Measurement_Accurate_DisplayViewBase.hpp>
#include <gui/measurement_accurate_display_screen/Measurement_Accurate_DisplayPresenter.hpp>

class Measurement_Accurate_DisplayView : public Measurement_Accurate_DisplayViewBase
{
public:
    Measurement_Accurate_DisplayView();
    virtual ~Measurement_Accurate_DisplayView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENT_ACCURATE_DISPLAYVIEW_HPP
