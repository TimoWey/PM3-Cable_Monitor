#ifndef MEASUREMENT_ACCURATE_DISPLAY_2PRESENTER_HPP
#define MEASUREMENT_ACCURATE_DISPLAY_2PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_Accurate_Display_2View;

class Measurement_Accurate_Display_2Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_Accurate_Display_2Presenter(Measurement_Accurate_Display_2View& v);

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

    virtual ~Measurement_Accurate_Display_2Presenter() {}

    virtual void setTimeoutValue(int value);

private:
    Measurement_Accurate_Display_2Presenter();

    Measurement_Accurate_Display_2View& view;
};

#endif // MEASUREMENT_ACCURATE_DISPLAY_2PRESENTER_HPP
