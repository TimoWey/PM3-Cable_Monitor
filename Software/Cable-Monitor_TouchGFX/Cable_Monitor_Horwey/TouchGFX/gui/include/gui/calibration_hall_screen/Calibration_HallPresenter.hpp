#ifndef CALIBRATION_HALLPRESENTER_HPP
#define CALIBRATION_HALLPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Calibration_HallView;

class Calibration_HallPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Calibration_HallPresenter(Calibration_HallView& v);

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

    virtual ~Calibration_HallPresenter() {}

private:
    Calibration_HallPresenter();

    Calibration_HallView& view;
};

#endif // CALIBRATION_HALLPRESENTER_HPP
