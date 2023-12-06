#ifndef CALIBRATION_PADPRESENTER_HPP
#define CALIBRATION_PADPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Calibration_PadView;

class Calibration_PadPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Calibration_PadPresenter(Calibration_PadView& v);

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

    virtual ~Calibration_PadPresenter() {}

    virtual void setTimeoutValue(int value);

private:
    Calibration_PadPresenter();

    Calibration_PadView& view;
};

#endif // CALIBRATION_PADPRESENTER_HPP
