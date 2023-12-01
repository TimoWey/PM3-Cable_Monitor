#ifndef MEASUREMENT_ACCURATE_DISPLAYPRESENTER_HPP
#define MEASUREMENT_ACCURATE_DISPLAYPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Measurement_Accurate_DisplayView;

class Measurement_Accurate_DisplayPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Measurement_Accurate_DisplayPresenter(Measurement_Accurate_DisplayView& v);

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

    virtual ~Measurement_Accurate_DisplayPresenter() {}

private:
    Measurement_Accurate_DisplayPresenter();

    Measurement_Accurate_DisplayView& view;
};

#endif // MEASUREMENT_ACCURATE_DISPLAYPRESENTER_HPP
