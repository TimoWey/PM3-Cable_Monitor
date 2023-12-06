#ifndef MEASUREMENT_SINGLEVIEW_HPP
#define MEASUREMENT_SINGLEVIEW_HPP

#include <gui_generated/measurement_single_screen/Measurement_SingleViewBase.hpp>
#include <gui/measurement_single_screen/Measurement_SinglePresenter.hpp>

class Measurement_SingleView : public Measurement_SingleViewBase
{
public:
    Measurement_SingleView();
    virtual ~Measurement_SingleView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void setTimeoutValue(int value);
protected:
};

#endif // MEASUREMENT_SINGLEVIEW_HPP
