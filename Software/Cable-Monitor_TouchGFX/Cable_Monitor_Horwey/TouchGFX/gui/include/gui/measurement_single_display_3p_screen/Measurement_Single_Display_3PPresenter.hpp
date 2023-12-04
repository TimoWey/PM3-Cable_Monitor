#ifndef MEASUREMENT_SINGLE_DISPLAY_3PPRESENTER_HPP
#define MEASUREMENT_SINGLE_DISPLAY_3PPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_Single_Display_3PView;

class Measurement_Single_Display_3PPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_Single_Display_3PPresenter(Measurement_Single_Display_3PView& v);

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

    virtual ~Measurement_Single_Display_3PPresenter() {}

    virtual void setTimeoutValue(int value);

private:
    Measurement_Single_Display_3PPresenter();

    Measurement_Single_Display_3PView& view;
};

#endif // MEASUREMENT_SINGLE_DISPLAY_3PPRESENTER_HPP
