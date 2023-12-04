#ifndef MEASUREMENT_SINGLEPRESENTER_HPP
#define MEASUREMENT_SINGLEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_SingleView;

class Measurement_SinglePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_SinglePresenter(Measurement_SingleView& v);

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

    virtual ~Measurement_SinglePresenter() {}

    virtual void setTimeoutValue(int value);

private:
    Measurement_SinglePresenter();

    Measurement_SingleView& view;
};

#endif // MEASUREMENT_SINGLEPRESENTER_HPP
