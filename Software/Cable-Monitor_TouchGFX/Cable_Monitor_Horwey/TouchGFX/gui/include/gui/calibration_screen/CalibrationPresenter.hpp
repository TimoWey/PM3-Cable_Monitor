#ifndef CALIBRATIONPRESENTER_HPP
#define CALIBRATIONPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class CalibrationView;

class CalibrationPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    CalibrationPresenter(CalibrationView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~CalibrationPresenter() {}

    virtual void setTimeoutValue(int value);

private:
    CalibrationPresenter();

    CalibrationView& view;
};

#endif // CALIBRATIONPRESENTER_HPP