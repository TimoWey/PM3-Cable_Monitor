#ifndef MEASUREMENT_SINGLE_DISPLAYVIEW_HPP
#define MEASUREMENT_SINGLE_DISPLAYVIEW_HPP

#include <gui_generated/measurement_single_display_screen/Measurement_Single_DisplayViewBase.hpp>
#include <gui/measurement_single_display_screen/Measurement_Single_DisplayPresenter.hpp>

class Measurement_Single_DisplayView : public Measurement_Single_DisplayViewBase
{
public:
    Measurement_Single_DisplayView();
    virtual ~Measurement_Single_DisplayView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // MEASUREMENT_SINGLE_DISPLAYVIEW_HPP
