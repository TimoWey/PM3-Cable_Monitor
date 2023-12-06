#ifndef MEASUREMENT_ACCURATEVIEW_HPP
#define MEASUREMENT_ACCURATEVIEW_HPP

#include <gui_generated/measurement_accurate_screen/Measurement_AccurateViewBase.hpp>
#include <gui/measurement_accurate_screen/Measurement_AccuratePresenter.hpp>

class Measurement_AccurateView : public Measurement_AccurateViewBase
{
public:
    Measurement_AccurateView();
    virtual ~Measurement_AccurateView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void setTimeoutValue(int value);
protected:
};

#endif // MEASUREMENT_ACCURATEVIEW_HPP
